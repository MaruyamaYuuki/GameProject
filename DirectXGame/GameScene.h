#pragma once
#include "KamataEngine.h"
#include "Timer.h"
#include "Screw.h"
#include "Rocket.h"

class GameScene {
public:

	GameScene();

	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon = nullptr;
	KamataEngine::Input* input = nullptr;
	KamataEngine::Camera camera_;

	KamataEngine::Model* model_ = nullptr;

	Timer* timer_ = nullptr;
	Screw* screw_ = nullptr;
	Rocket* rocket_ = nullptr;

	bool screwFlag = false;
	bool countFlag = false;
};
