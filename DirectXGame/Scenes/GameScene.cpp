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

	// 設定の初期化・読み込み
	setting_ = new Setting();
	setting_->Load();
	// タイマーの初期化・生成
	timer_ = new Timer();
	timer_->Initialize();
	// ネジの初期化・生成
	screw_ = new Screw();
	screw_->Initialize(modelScrew_, input,timer_);
	// ロケットの初期化・生成
	rocket_ = new Rocket();
	rocket_->Initialize(modelRocket_, input, screw_, timer_, setting_);
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
	ui_->InitializeGameUI(timer_, rocket_,setting_);
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
	Input::GetInstance()->GetJoystickState(0, state);
	Input::GetInstance()->GetJoystickStatePrevious(0, preState);
	
	FiringAfterSelect();

	if (input->TriggerKey(DIK_S)) {
		screwFlag = true;
	}

	universedome_->Update();
	skydome_->Update();
	skydome_->UpdateAlphaByDistance(rocket_->GetWorldTransform().translation_);

	field_->Update();

	timer_->Update();

	timer_->ScrewTimer(screwFlag);
	timer_->FiringCountTimer();

	screw_->Update();
	rocket_->Update();

	ui_->Update();

	fade_ = new Fade();
	fade_->Initialize();

	cameraController_->Update();
	DebugText::GetInstance()->ConsolePrintf("SelectNum : %d\n", selectNum_);

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

	fade_->Draw();

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}

void GameScene::FiringAfterSelect() {
	bool isRightPressed = input->TriggerKey(DIK_RIGHT) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	bool isLeftPressed = input->TriggerKey(DIK_LEFT) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	bool isSpacePressed = input->TriggerKey(DIK_SPACE);
	bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

	if (rocket_->IsArrived()) {
		if (isRightPressed || isLeftPressed) {
			if (selectNum_ == 1) {
				selectNum_ = 2;
			} else {
				selectNum_ = 1;
			}
		}

		ui_->UpdateAfterSelect(selectNum_);

		if (isSpacePressed || isAButtonPressed) {
			switch (selectNum_) {
			case 1:
				// リトライ
				fade_->Start(Fade::Status::FadeOut, 1.0f);
				afterSelectState_ = AfterSelectState::FadeOutToRetry;
				break;
			case 2:
				setting_->UpdateBestRecord(rocket_->GetRecord());
				fade_->Start(Fade::Status::FadeOut, 1.0f);
				afterSelectState_ = AfterSelectState::FadeOutToTitle;
				break;
			}
		}
	}

	switch (afterSelectState_) {
	case GameScene::AfterSelectState::FadeOutToRetry:
		fade_->Update();
		if (fade_->IsFinished()) {
			// リセット
			timer_->Reset();
			rocket_->Reset();
			screw_->Reset();
			ui_->Reset();
			screwFlag = false;

			// フェードイン開始
			fade_->Start(Fade::Status::FadeIn, 1.0f);
			afterSelectState_ = AfterSelectState::FadeInRetry;
		}
		break;
	case GameScene::AfterSelectState::FadeInRetry:
		fade_->Update();
		if (fade_->IsFinished()) {
			afterSelectState_ = AfterSelectState::None;
		}
		break;
	case GameScene::AfterSelectState::FadeOutToTitle:
		if (fade_->IsFinished()) {
			isFinished_ = true;
		}
		break;
	}
}
