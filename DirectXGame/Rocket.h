#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Screw;
class Timer;
class Rocket {
	enum class FiringState { 
		Standby, 
		ReadyToFire, 
		Firing };


public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input, Screw* screw, Timer* timer);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	void Firing();

	const WorldTransformEx& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

private:
	WorldTransformEx worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Vector3 velocity_ = {};

	bool testFlag_ = false;
	bool isFiring_ = false;

	float screwCount_ = 0;   // ネジを巻いた回数

	float maxFiringDistance_ = 9999; // 最大飛距離
	float firingDistance_ = 0;       // 飛距離

	Screw* screw_ = nullptr;
	Timer* timer_ = nullptr;

	bool hit = false;
};
