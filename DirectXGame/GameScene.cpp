#include "GameScene.h"
#include "Rocket.h"
#include <cfloat>

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete timer_;
	delete screw_;
	delete rocket_;
	delete model_;
	delete cameraController_;
}

void GameScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();

	model_ = Model::Create();


	// タイマーの初期化・生成
	timer_ = new Timer();
	timer_->Initialize();
	// ネジの初期化・生成
	screw_ = new Screw();
	screw_->Initialize(model_, input, timer_);
	// ロケットの初期化・生成
	rocket_ = new Rocket();
	rocket_->Initialize(model_, input, screw_, timer_);
	// カメラコントローラの初期化・生成
	cameraController_ = new CameraController(); 
	cameraController_->Initialize();            
	cameraController_->SetTarget(rocket_);      // 追従対象をセット
	cameraController_->Reset();                 // リセット(瞬間合わせ)
	CameraController::Rect cameraArea = {0.0f, 1280.0f, -FLT_MAX, 720.0f};
	cameraController_->SetMoveableArea(cameraArea);
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

	cameraController_->Update();

	const Camera& cameraViewProjection = cameraController_->GetCamera();
	camera_.matView = cameraViewProjection.matView;
	camera_.matProjection = cameraViewProjection.matProjection;
	camera_.TransferMatrix();
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
