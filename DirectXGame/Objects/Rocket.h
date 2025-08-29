#pragma once
#include "KamataEngine.h"
#include "../WorldTransformEx.h"


class Screw;
class Timer;
class Setting;
class Rocket {

public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input, Screw* screw , Timer* timer, Setting* setting);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	void InitializeOnlyModel(KamataEngine::Model* model);

	void UpdateOnlyModel();

	void Firing();

	void Move();

	void Reset();

	const WorldTransformEx& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	bool IsFiring() const { return isFiring_; }

	bool IsDrawRecords() const { return isDrawRecords_; }

	bool IsDrawBestRecord() const { return isDrawBestRecord_; }

	bool IsArrived() const { return isArrived; }

	float GetRecord() const { return firingDistance_; }

private:
	WorldTransformEx worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Vector3 velocity_ = {1.0f, 0.0f, 0.0f};

	bool isFiring_ = false;
	bool isDrawRecords_ = false;
	bool isDrawBestRecord_ = false;
	bool isArrived = false;
	bool isTimerStart_ = false;

	float screwCount_ = 0;   // ネジを巻いた回数

	float maxFiringDistance_ = 999; // 最大飛距離
	float firingDistance_ = 0;       // 飛距離

	Screw* screw_ = nullptr;
	Timer* timer_ = nullptr;
	Setting* setting_ = nullptr;
	
	float rocketWidth = 1.0f; // ロケットの幅
	float waitingTime_ = 60.0f; // 到達後の待機時間(フレーム)
};
