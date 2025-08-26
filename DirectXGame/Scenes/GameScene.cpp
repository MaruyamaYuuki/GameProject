#include "GameScene.h"
#include <cfloat>

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelRocket_;
	delete modelScrew_;
	delete modelSkydome_;
	delete modelUniversedome_;
	delete modelField_;

	delete timer_;
	delete screw_;
	delete rocket_;
	delete skydome_;
	delete universedome_;
	delete cameraController_;
	delete debugCamera_;
	delete field_;
	delete ui_;
}

void GameScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	//camera_.nearZ = 0.05f;
	camera_.farZ = 50000.0f;
	camera_.Initialize();

	model_ = Model::Create();
	modelRocket_ = Model::CreateFromOBJ("rocket", true);
	modelScrew_ = Model::CreateFromOBJ("screw", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelUniversedome_ = Model::CreateFromOBJ("universedome", true);
	modelField_ = Model::CreateFromOBJ("field", true);

	// タイマーの初期化・生成
	timer_ = new Timer();
	timer_->Initialize();
	// ネジの初期化・生成
	screw_ = new Screw();
	screw_->Initialize(modelScrew_, input,timer_);
	// ロケットの初期化・生成
	rocket_ = new Rocket();
	rocket_->Initialize(modelRocket_, input, screw_, timer_);
	// 天球の初期化・生成
	universedome_ = new Skydome();
	universedome_->Initialize(modelUniversedome_, universeSize_, &camera_);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, skySize_, &camera_);
	// フィールドの初期化・生成
	field_ = new Field();
	field_->Initialize(modelField_);
	// UIの初期化・生成
	ui_ = new UI();
	ui_->Initialize(timer_);
	// カメラコントローラの初期化・生成
	cameraController_ = new CameraController(); 
	cameraController_->Initialize();            
	cameraController_->SetTarget(rocket_);      // 追従対象をセット
	cameraController_->Reset();                 // リセット(瞬間合わせ)
	CameraController::Rect cameraArea = {0.0f, 1280.0f, -FLT_MAX, 720.0f};
	cameraController_->SetMoveableArea(cameraArea);

	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {
	if (input->TriggerKey(DIK_S)) {
		screwFlag = true;
	}

	universedome_->Update();
	skydome_->Update();
	skydome_->UpdateAlphaByDistance(rocket_->GetWorldTransform().translation_);

	field_->Update();

	timer_->Update();

	timer_->ScrewTimer(screwFlag);
	timer_->FiringCountTimer(cameraController_->CameraZoomOuted());

	screw_->Update();
	rocket_->Update();

	ui_->Update();
	ui_->UpdateScore(rocket_->GetWorldTransform().translation_.y);

	cameraController_->Update(timer_->IsZoomOut());
	DebugText::GetInstance()->ConsolePrintf("Flag : %d\n", cameraController_->CameraZoomOuted());

	// カメラの処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		const Camera& cameraViewProjection = cameraController_->GetCamera();
		camera_.matView = cameraViewProjection.matView;
		camera_.matProjection = cameraViewProjection.matProjection;
		camera_.TransferMatrix();
	}

	#ifdef _DEBUG
	if (input->TriggerKey(DIK_RETURN)) {
		if (!isDebugCameraActive_)
			isDebugCameraActive_ = true;
		else
			isDebugCameraActive_ = false;
	}
    #endif
}

void GameScene::Draw() {

	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画後処理
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	universedome_->Draw();
	skydome_->Draw();

	field_->Draw(camera_);

	screw_->Draw(camera_);

	rocket_->Draw(camera_);



	// 3Dオブジェクト描画後処理
	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());
	ui_->Draw();

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}
