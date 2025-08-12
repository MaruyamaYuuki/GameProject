#pragma once
#include "KamataEngine.h"
#include "Timer.h"
#include "Screw.h"
#include "Rocket.h"
#include "CameraController.h"
#include "Skydome.h"

class GameScene {
public:

	GameScene();

	~GameScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return isFinished_; }

private:
	KamataEngine::DirectXCommon* dxCommon = nullptr;
	KamataEngine::Input* input = nullptr;
	KamataEngine::Camera camera_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelRocket_ = nullptr;
	KamataEngine::Model* modelScrew_ = nullptr;
	KamataEngine::Model* modelSkydome_ = nullptr;
	KamataEngine::Model* modelUniversedome_ = nullptr;

	Timer* timer_ = nullptr;
	Screw* screw_ = nullptr;
	Rocket* rocket_ = nullptr;
	CameraController* cameraController_ = nullptr;

	Skydome* skydome_ = nullptr;
	Skydome* universedome_ = nullptr;

	bool screwFlag = false;
	bool countFlag = false;

	bool isFinished_ = false;
};
