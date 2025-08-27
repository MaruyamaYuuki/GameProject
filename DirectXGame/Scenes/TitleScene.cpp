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
	delete spriteCommands_;
}

void TitleScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();

	camera_.translation_ = {0.0f, 0.0f, startDistance};

	commandNum_ = 1;
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

	textureHandleTitle_ = TextureManager::Load("title.png");
	textureHandleStart_ = TextureManager::Load("commands/startCommand.png");
	textureHandleRule_ = TextureManager::Load("commands/ruleCommand.png");
	textureHandleExit_ = TextureManager::Load("commands/exitCommand.png");
	textureHandleSetting_ = TextureManager::Load("commands/settingCommand.png");

	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0.0f, 0.0f});
	spriteCommands_ = Sprite::Create(textureHandleStart_, {0.0f, 0.0f});
}

void TitleScene::Update() {

	spriteTitle_->SetPosition({0.0f, -50.0f});
	spriteCommands_->SetPosition({0.0f, -25.0f});

	Input::GetInstance()->GetJoystickState(0, state);
	Input::GetInstance()->GetJoystickStatePrevious(0, preState);

	SelectCommand();

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
	bool isUpPressed = input->TriggerKey(DIK_UP) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP); 
	bool isDownPressed = input->TriggerKey(DIK_DOWN) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	bool isRightPressed = input->TriggerKey(DIK_RIGHT) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	bool isLeftPressed = input->TriggerKey(DIK_LEFT) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	bool isSpacePressed = input->TriggerKey(DIK_SPACE);
	bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

	if (isUpPressed) {
		commandNum_--;
		if (commandNum_ < 1) {
			commandNum_ = 3;
		}
	} else if (isDownPressed) {
		commandNum_++;
		if (commandNum_ > 3) {
			commandNum_ = 1;
		}
	}

	if (isRightPressed || isLeftPressed) {
		if (!isSettingChoice_) {
			isSettingChoice_ = true;
		} else {
			isSettingChoice_ = false;
			commandNum_ = 1;
		}
	}

	if (isSpacePressed || isAButtonPressed) {
		if (!isSettingChoice_) {
			switch (commandNum_) {
			case 1: // Start
				isMove_ = true;
				break;
			case 2: // Rule
				isOpenRule_ = true;
				break;
			case 3: // Exit
				isExit_ = true;
				break;
			}
		} else {
			isOpenSetting_ = true;
		}
	}
}
