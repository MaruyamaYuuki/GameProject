#pragma once
#include "KamataEngine.h"
#include "Rocket.h"
#include "Screw.h"
#include "Skydome.h"
#include "Field.h"

class TitleScene {

public:
	TitleScene();

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	void CameraMove();

	bool IsFinished() const { return isFinished_;}

private:
	XINPUT_STATE state, preState;

	KamataEngine::DirectXCommon* dxCommon = nullptr;
	KamataEngine::Input* input = nullptr;

	KamataEngine::Camera camera_;
	float distance = 30.0f; // CameraController で使ってる距離と同じにする

	KamataEngine::Model* modelRocket_ = nullptr;
	KamataEngine::Model* modelScrew_ = nullptr;
	KamataEngine::Model* modelSkydome_ = nullptr;
	KamataEngine::Model* modelField_ = nullptr;

	KamataEngine::Sprite* spriteTitle_ = nullptr;
	uint32_t textureHandleTitle_ = 0;

	Screw* screw_ = nullptr;
	Rocket* rocket_ = nullptr;

	Skydome* skydome_ = nullptr;

	Field* field_ = nullptr;
	
	bool isMove_ = false;
	bool isFinished_ = false;

	float position_ = 0.0f;

};
