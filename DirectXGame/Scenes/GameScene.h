#pragma once
#include "KamataEngine.h"
#include "../Timer.h"
#include "../Objects/Screw.h"
#include "../Objects/Rocket.h"
#include "../CameraController.h"
#include "../Objects/Skydome.h"
#include "../Objects/Field.h"
#include "../UI.h"

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
	KamataEngine::Model* modelField_ = nullptr;

	Timer* timer_ = nullptr;
	Screw* screw_ = nullptr;
	Rocket* rocket_ = nullptr;
	CameraController* cameraController_ = nullptr;

	Skydome* skydome_ = nullptr;
	Skydome* universedome_ = nullptr;

	Field* field_ = nullptr;

	UI* ui_ = nullptr;

	bool screwFlag = false;

	bool isFinished_ = false;

	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	KamataEngine::Vector3 skySize_ = {900.0f, 900.0f, 900.0f};
	KamataEngine::Vector3 universeSize_{11000.0f, 11000.0f, 950.0f};
};
