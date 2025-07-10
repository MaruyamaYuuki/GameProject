#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Rocket {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input);

	void Update();

	void Draw();

private:
	WorldTransformEx worldTrandform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	bool testFlag = false;
};
