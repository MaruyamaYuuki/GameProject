#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Rocket {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input);

	void Update();

	void Draw();

	void Firing();

private:
	WorldTransformEx worldTrandform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	bool testFlag_ = false;
	bool isFiring_ = false;

	float screwCount_ = 0;   // ネジを巻いた回数

	float maxFiringDistance_ = 9999; // 最大飛距離
	float firingDistance_ = 0;       // 飛距離
};
