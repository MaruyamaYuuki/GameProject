#pragma once
#include "KamataEngine.h"
#include "Rocket.h"
#include "Screw.h"
#include "Skydome.h"

class TitleScene {

public:
	TitleScene();

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

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

	Screw* screw_ = nullptr;
	Rocket* rocket_ = nullptr;

	Skydome* skydome_ = nullptr;

	bool isFinished_ = false;
};
