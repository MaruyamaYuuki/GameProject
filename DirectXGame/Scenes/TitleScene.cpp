#include "TitleScene.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete rocket_;
	delete screw_;
	delete skydome_;
	delete field_;
	delete setting_;
	delete ui_;
	delete fade_;

	delete modelRocket_;
	delete modelScrew_;
	delete modelSkydome_;
	delete modelField_;

	delete spriteTitle_;
	delete spriteCommands_;
}

void TitleScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();
	audio_ = Audio::GetInstance();

	camera_.Initialize();

	camera_.translation_ = {0.0f, 0.0f, startDistance};

	commandNum_ = 1;
	spriteAlpha_ = 1.0f;
	isSettingChoice_ = false;
	isMove_ = false;
	isOpenRule_ = false;
	isExit_ = false;
	isOpenSetting_ = false;
	isFinished_ = false;

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

	setting_ = new Setting();
	setting_->Load();
	ui_ = new UI();
	ui_->InitializeTitleUI(setting_);

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, fadeTime_);

	textureHandleTitle_ = TextureManager::Load("title.png");
	textureHandleStart_ = TextureManager::Load("commands/startCommand.png");
	textureHandleRule_ = TextureManager::Load("commands/ruleCommand.png");
	textureHandleExit_ = TextureManager::Load("commands/exitCommand.png");
	textureHandleSetting_ = TextureManager::Load("commands/settingCommand.png");

	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0.0f, 0.0f});
	spriteCommands_ = Sprite::Create(textureHandleStart_, {0.0f, 0.0f});

	bgmDataHandle_ = audio_->LoadWave("sounds/titleBGM.wav");
	selectSEDataHandle_ = audio_->LoadWave("sounds/maou_se_system13.wav");
	pushSEDataHandle_ = audio_->LoadWave("sounds/maou_se_system11.wav");
}

void TitleScene::Update() {

	spriteTitle_->SetPosition({0.0f, 0.0f});
	spriteCommands_->SetPosition({0.0f, -25.0f});

	Input::GetInstance()->GetJoystickState(0, state);
	Input::GetInstance()->GetJoystickStatePrevious(0, preState);

	isUpPressed = input->TriggerKey(DIK_UP) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
	isDownPressed = input->TriggerKey(DIK_DOWN) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	isRightPressed = input->TriggerKey(DIK_RIGHT) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	isLeftPressed = input->TriggerKey(DIK_LEFT) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	isSpacePressed = input->TriggerKey(DIK_SPACE);
	isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

	switch (phase_) {
	case TitleScene::Phase::kFadeIn:
		fade_->Update();
		if (fade_->IsFinished()) {
			fade_->Stop();
    		bgmVoiceHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.7f);
			phase_ = Phase::kMain;
		}
		break;
	case TitleScene::Phase::kMain:
    	SelectCommand();
		break;
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

	if (isOpenRule_) {
		if (!justOpened_) {
			if (isSpacePressed || isAButtonPressed) {
				pushSEVoiceHandle_ = audio_->PlayWave(pushSEDataHandle_, false, 0.5f);
				isOpenRule_ = false;
			}
		} else {
			justOpened_ = false; // 1フレーム経過したら解除
		}
	}

	SetGamePadConfig();

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

		spriteCommands_->SetColor({1.0f, 1.0f, 1.0f, spriteAlpha_});
		if (!isSettingChoice_) {
			switch (commandNum_) {
			case 1: // Start
				spriteCommands_->SetTextureHandle(textureHandleStart_);
				break;
			case 2: // Rule
				spriteCommands_->SetTextureHandle(textureHandleRule_);
				break;
			case 3: // Exit
				spriteCommands_->SetTextureHandle(textureHandleExit_);
				break;
			}
		} else {
			spriteCommands_->SetTextureHandle(textureHandleSetting_);
		}
		spriteCommands_->Draw();
	}

	if (isOpenRule_) {
		ui_->DrawRule();
	}

	if (isOpenSetting_) {
		ui_->DrawGamePadConfig();
	}

	fade_->Draw();
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

void TitleScene::SelectCommand() { 

	if (!isMove_ && !isOpenRule_ && !isOpenSetting_) {
    	if (isUpPressed) {
			selectSEVoiceHandle_ = audio_->PlayWave(selectSEDataHandle_, false, 0.5f);
    		commandNum_--;
    		if (commandNum_ < 1) {
    			commandNum_ = 3;
    		}
    	} else if (isDownPressed) {
			selectSEVoiceHandle_ = audio_->PlayWave(selectSEDataHandle_, false, 0.5f);
    		commandNum_++;
    		if (commandNum_ > 3) {
    			commandNum_ = 1;
    		}
    	}

    	if (isRightPressed || isLeftPressed) {
			selectSEVoiceHandle_ = audio_->PlayWave(selectSEDataHandle_, false, 0.5f);
    		if (!isSettingChoice_) {
    			isSettingChoice_ = true;
    		} else {
    			isSettingChoice_ = false;
    			commandNum_ = 1;
    		}
    	}

    	if (isSpacePressed || isAButtonPressed) {
			pushSEVoiceHandle_ = audio_->PlayWave(pushSEDataHandle_, false, 0.5f);
    		if (!isSettingChoice_) {
    			switch (commandNum_) {
    			case 1: // Start
					audio_->StopWave(bgmVoiceHandle_);
    				isMove_ = true;
    				break;
    			case 2: // Rule
    				isOpenRule_ = true;
					justOpened_ = true;
    				break;
    			case 3: // Exit
    				isExit_ = true;
    				break;
    			}
    		} else {
    			isOpenSetting_ = true;
				justOpened_ = true;
    		}
    	}
	}
}

void TitleScene::SetGamePadConfig() {
	bool isChanged = false;
	if (isOpenSetting_) {
        ui_->UpdateGamePadConfig();

    	if (isLeftPressed || isRightPressed) {
			selectSEVoiceHandle_ = audio_->PlayWave(selectSEDataHandle_, false, 0.5f);
    		if (setting_->screwInputType_ == "AButton") {
    			setting_->screwInputType_ = "Stick";
    		} else if (setting_->screwInputType_ == "Stick") {
    			setting_->screwInputType_ = "AButton";
    		}
    		isChanged = true;
    	}

    	// 変更があった時だけ保存
    	if (isChanged) {
        	setting_->Save();
    	}
 
        if (!justOpened_) {
			if (isSpacePressed || isAButtonPressed) {
				pushSEVoiceHandle_ = audio_->PlayWave(pushSEDataHandle_, false, 0.5f);
				isOpenSetting_ = false;
			}
		} else {
			justOpened_ = false; // 1フレーム経過したら解除
		}
	}
}
