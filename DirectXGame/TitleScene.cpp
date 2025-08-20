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
}

void TitleScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();

// --- カメラの位置を少し上に、奥に配置する ---
	camera_.translation_ = {0.0f, 0.0f, -distance};

	// --- カメラを下方向に傾ける（X軸回転を追加）---
	//camera_.rotation_ = {0.1f, 0.0f, 0.0f}; 

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
	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0.0f, 0.0f});

}

void TitleScene::Update() {
	bool isSpacePressed = input->TriggerKey(DIK_SPACE);
	bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

	if (isSpacePressed || isAButtonPressed) {
		isFinished_ = true;
	}

	skydome_->Update();

	field_->Update();

	screw_->UpdateOnlyModel();
	rocket_->UpdateOnlyModel();

	CameraMove();
	DebugText::GetInstance()->ConsolePrintf("Flag : %d\nCameraYPosition : %f\n", isMove_, camera_.translation_.y);

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

	//spriteTitle_->Draw();

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}

void TitleScene::CameraMove() {
	if (isMove_) {
		if (position_ > 0.0f) {
			position_ -= 0.1f;
		}
		camera_.translation_.y = position_;
	}
}
