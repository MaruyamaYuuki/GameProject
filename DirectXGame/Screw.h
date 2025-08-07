#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Timer;
class Screw {
	enum class ScrewType {
		Button,
		Joystick,
	};

public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input, Timer* timer);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	void InitializeOnlyModel(KamataEngine::Model* model);

	void UpdateOnlyModel();

	void ScrewWinding();

	float GetEnergy() { return energy_; }

private:
	XINPUT_STATE state, preState;

	WorldTransformEx worldTransform_;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Model* model_ = nullptr;

	float energy_ = 0;

	bool testFlag = false;

	Timer* timer_ = nullptr;

	float targetRotationX_ = 0.0f; // 回転目標角（ラジアン）
	float rotationSpeed_ = 15.0f;   // 回転スピード（ラジアン/秒）

	float previousStickAngle_ = 0.0f; // 前回のスティック角度
	float accumulatedAngle_ = 0.0f;   // 合計回転数

	ScrewType screwType_ = ScrewType::Button;
};
