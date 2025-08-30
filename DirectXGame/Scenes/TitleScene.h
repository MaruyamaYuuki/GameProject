#pragma once
#include "KamataEngine.h"
#include "../Objects/Rocket.h"
#include "../Objects/Screw.h"
#include "../Objects/Skydome.h"
#include "../Objects/Field.h"
#include "../Setting.h"
#include "../UI.h"
#include "../Fade.h"

class TitleScene {
public:
	enum class Phase {
		kFadeIn,
		kMain,
	};

public:
	TitleScene();

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	void CameraMove();

	void SelectCommand();

	void SetGamePadConfig();

	bool IsOpenRule() const { return isOpenRule_; }

	bool IsExit() const { return isExit_; }

	bool IsOpenSetting() const { return isOpenSetting_; }

	bool IsFinished() const { return isFinished_;}

private:
	XINPUT_STATE state, preState;

	KamataEngine::DirectXCommon* dxCommon = nullptr;
	KamataEngine::Input* input = nullptr;

	KamataEngine::Camera camera_;
	float startDistance = -40.0f;
	float zoomUpDistance = -20.0f; // CameraController で使ってる距離と同じにする

	KamataEngine::Model* modelRocket_ = nullptr;
	KamataEngine::Model* modelScrew_ = nullptr;
	KamataEngine::Model* modelSkydome_ = nullptr;
	KamataEngine::Model* modelField_ = nullptr;

	KamataEngine::Sprite* spriteTitle_ = nullptr;
	KamataEngine::Sprite* spriteCommands_ = nullptr;

	uint32_t textureHandleTitle_ = 0;
	uint32_t textureHandleStart_ = 0;
	uint32_t textureHandleRule_ = 0;
	uint32_t textureHandleExit_ = 0;
	uint32_t textureHandleSetting_ = 0;

	Screw* screw_ = nullptr;
	Rocket* rocket_ = nullptr;
	Skydome* skydome_ = nullptr;
	Field* field_ = nullptr;
	Setting* setting_ = nullptr;
	UI* ui_ = nullptr;
	Fade* fade_ = nullptr;
	
	bool isSettingChoice_ = false;
	bool isMove_ = false;
	bool isOpenRule_ = false;
	bool isExit_ = false;
	bool isOpenSetting_ = false;
	bool isFinished_ = false;
	bool justOpenedSetting_ = false;

	bool isUpPressed;
	bool isDownPressed;
	bool isRightPressed;
	bool isLeftPressed;
	bool isSpacePressed;
	bool isAButtonPressed;

	float spriteAlpha_ = 1.0f; // スプライトの透明度(初期値: 不透明)
	float fadeSpeed_ = 0.02f;  // フェードアウト速度
	float fadeTime_ = 0.5f;

	int commandNum_ = 1;

	Phase phase_ = Phase::kFadeIn;
};
