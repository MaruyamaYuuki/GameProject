#include "GameScene.h"
#include "Rocket.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete timer_;
	delete screw_;
	delete rocket_;
	delete model_;
}

void GameScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();

	model_ = Model::Create();

	timer_ = new Timer();
	timer_->Initialize();

	screw_ = new Screw();
	screw_->Initialize(model_, input, timer_);

	rocket_ = new Rocket();
	rocket_->Initialize(model_, input, screw_, timer_);
}

void GameScene::Update() {
	if (input->TriggerKey(DIK_S)) {
		screwFlag = true;
	}
	if (input->TriggerKey(DIK_C)) {
		countFlag = true;
	}

	timer_->Update();

	timer_->ScrewTimer(screwFlag);
	timer_->FiringCountTimer(countFlag);

	screw_->Update();
	rocket_->Update();
}

void GameScene::Draw() {

	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画後処理
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	screw_->Draw(camera_);

	rocket_->Draw(camera_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}
