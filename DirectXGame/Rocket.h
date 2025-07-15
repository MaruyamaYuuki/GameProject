#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Screw;
class Timer;
class Rocket {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input, Screw* screw, Timer* timer);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	void Firing();

private:
	WorldTransformEx worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	bool testFlag_ = false;
	bool isFiring_ = false;

	float screwCount_ = 0;   // ネジを巻いた回数

	float maxFiringDistance_ = 9999; // 最大飛距離
	float firingDistance_ = 0;       // 飛距離

	Screw* screw_ = nullptr;
	Timer* timer_ = nullptr;
};
