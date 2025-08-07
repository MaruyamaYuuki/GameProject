#pragma once
#include "KamataEngine.h"
#include "Rocket.h"
#include "Screw.h"

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


	bool isFinished_ = false;
};
