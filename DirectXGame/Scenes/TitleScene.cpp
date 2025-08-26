#include "TitleScene.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete rocket_;
	delete screw_;
	delete skydome_;
	delete field_;

	delete modelRocket_;
	delete modelScrew_;
	delete modelSkydome_;
	delete modelField_;

	delete spriteTitle_;
	delete spriteStart_;
}

void TitleScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();

	camera_.translation_ = {0.0f, 0.0f, startDistance};

	modelRocket_ = Model::CreateFromOBJ("rocket", true);
	modelScrew_ = Model::CreateFromOBJ("screw", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelField_ = Model::CreateFromOBJ("field", true);

	screw_ = new Screw();
	screw_->InitializeOnlyModel(modelScrew_);

	rocket_ = new Rocket();
	rocket_->InitializeOnlyModel(modelRocket_);

	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, Vector3{900.0f, 900.0f, 900.0f}, &camera_);

	field_ = new Field();
	field_->Initialize(modelField_);

	textureHandleTitle_ = TextureManager::Load("testTitle.png");
	textureHandleStartToSpace_ = TextureManager::Load("startToSpace.png");
	textureHandleStartToA_ = TextureManager::Load("startToA.png");

	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0.0f, 0.0f});
	spriteStart_ = Sprite::Create(textureHandleStartToSpace_, {0.0f, 0.0f});
}

void TitleScene::Update() {

	Input::GetInstance()->GetJoystickState(0, state);
	Input::GetInstance()->GetJoystickStatePrevious(0, preState);

	bool isSpacePressed = input->TriggerKey(DIK_SPACE);
	bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

	SwitchStartTexture();

	if (isSpacePressed || isAButtonPressed) {
		isMove_ = true;
	}

    // フェードアウト処理
	if (isMove_) {
		if (spriteAlpha_ > 0.0f) {
			spriteAlpha_ -= fadeSpeed_;
			if (spriteAlpha_ < 0.0f) {
				spriteAlpha_ = 0.0f; // 負値にならないように固定
			}
		}
	}

	skydome_->Update();

	field_->Update();

	screw_->UpdateOnlyModel();
	rocket_->UpdateOnlyModel();

	CameraMove();

	camera_.UpdateMatrix();
}

void TitleScene::Draw() {
	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画後処理
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(dxCommon->GetCommandList());
	skydome_->Draw();

	field_->Draw(camera_);

	screw_->Draw(camera_);
	rocket_->Draw(camera_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();


	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

    if (spriteAlpha_ > 0.0f) {
		spriteTitle_->SetColor({1.0f, 1.0f, 1.0f, spriteAlpha_});
		spriteTitle_->Draw();

		spriteStart_->SetColor({1.0f, 1.0f, 1.0f, spriteAlpha_});
		spriteStart_->Draw();
	}

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}

void TitleScene::CameraMove() {
	if (isMove_) {
		float kLerpRate = 0.05f; // 補間速度（好みで調整）

		// ズームアップの処理（Z軸だけ動かす）
		if (isMove_) {
			camera_.translation_.z = Lerp(camera_.translation_.z, zoomUpDistance, kLerpRate);

			// 誤差吸収：目標に十分近づいたらスナップ
			if (fabs(camera_.translation_.z - zoomUpDistance) < 0.01f) {
				camera_.translation_.z = zoomUpDistance;
			}
		} else {
			// 初期状態でのカメラ距離
			camera_.translation_.z = startDistance;
		}
	}

	if (camera_.translation_.z == zoomUpDistance) {
		isFinished_ = true;
	}
}

void TitleScene::SwitchStartTexture() {
	// コントローラー接続判定
	bool isControllerConnected = input->IsControllerConnected();

	if (isControllerConnected) {
		spriteStart_->SetTextureHandle(textureHandleStartToA_);
	} else {
		spriteStart_->SetTextureHandle(textureHandleStartToSpace_);
	}
}
