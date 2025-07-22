#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Timer;
class Screw {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input, Timer* timer);

	void Update();

	void Draw(KamataEngine::Camera& camera);

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
	float rotationSpeed_ = 5.0f;   // 回転スピード（ラジアン/秒）
};
