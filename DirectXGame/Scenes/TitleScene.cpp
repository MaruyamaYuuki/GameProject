#include "TitleScene.h"

using namespace KamataEngine;

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

	camera_.translation_ = {0.0f, 0.0f, -distance};
	camera_.rotation_.x = -0.8f;

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

	spriteTitle_->Draw();
	if (!isMove_) {
    	spriteStart_->Draw();
	}


	// 前景スプライト描画後処理
	Sprite::PostDraw();
}

void TitleScene::CameraMove() {
	if (isMove_) {

		// 回転をじわじわ 0 に近づける
		if (camera_.rotation_.x < 0.0f) {
			camera_.rotation_.x += 0.005f; // 数値は調整
			if (camera_.rotation_.x > 0.0f) {
				camera_.rotation_.x = 0.0f; // オーバー防止
				isFinished_ = true;
			}
		}
	}

	// rotation.x の値に応じてスプライトのアルファを変える
	// 初期値を -0.3f として、0.0f で透明になるように
	float t = camera_.rotation_.x / -0.3f; // -0.3 → 1, 0 → 0
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;

	// Sprite の色を設定（RGBA）
	spriteTitle_->SetColor({1.0f, 1.0f, 1.0f, t});
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
