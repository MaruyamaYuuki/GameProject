#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete rocket_;
	delete screw_;

	delete modelRocket_;
	delete modelScrew_;
}

void TitleScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();



	// 真後ろから見下ろす感じなら
	camera_.translation_ = {0.0f, 0.0f, -distance};

	modelRocket_ = Model::CreateFromOBJ("rocket", true);
	modelScrew_ = Model::CreateFromOBJ("screw", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	screw_ = new Screw();
	screw_->InitializeOnlyModel(modelScrew_);

	rocket_ = new Rocket();
	rocket_->InitializeOnlyModel(modelRocket_);

	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, Vector3{900.0f, 900.0f, 900.0f}, &camera_);

}

void TitleScene::Update() {
	bool isSpacePressed = input->TriggerKey(DIK_SPACE);
	bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

	if (isSpacePressed || isAButtonPressed) {
		isFinished_ = true;
	}

	skydome_->Update();

	screw_->UpdateOnlyModel();
	rocket_->UpdateOnlyModel();

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

	screw_->Draw(camera_);
	rocket_->Draw(camera_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();



	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}
