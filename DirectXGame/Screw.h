#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Timer;
class Screw {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Input* input, Timer* timer);

	void Update();

	void Draw();

	void ScrewWinding();

	float GetEnergy() { return energy_; }

private:
	XINPUT_STATE state, preState;

	WorldTransformEx worldTransfor_;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Model* model_ = nullptr;

	float energy_ = 0;

	bool testFlag = false;

	Timer* timer_ = nullptr;
};
