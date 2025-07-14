#include "Rocket.h"
#include "Screw.h"
#include "Timer.h"
#include <cassert>

using namespace KamataEngine;

void Rocket::Initialize(Model* model, Input* input, Screw* screw, Timer* timer) {
	assert(model);
	model_ = model;
	assert(input);
	input_ = input;
	assert(screw);
	screw_ = screw;
	assert(timer);
	timer_ = timer;

	worldTrandform_.Initialize();
}

void Rocket::Update() { 
	Firing();

	DebugText::GetInstance()->ConsolePrintf("FiringDistance : %f\n", firingDistance_);

	worldTrandform_.UpdateMatrix(); 
}

void Rocket::Draw() {}

void Rocket::Firing() {
	screwCount_ = screw_->GetEnergy();

	if (timer_->IsScrewStart()) {
		// ネジを巻いた回数に応じて距離を決定
		const float distanceperScrew = 80.0f;
		firingDistance_ = screwCount_ * distanceperScrew;

		// 距離制限
		if (firingDistance_ > maxFiringDistance_) {
			firingDistance_ = maxFiringDistance_;
		}

		isFiring_ = true;
	}
	if (isFiring_) {
		worldTrandform_.translation_.y -= 1.0f;

		// 飛びすぎ防止
		if (worldTrandform_.translation_.z >= firingDistance_) {
			testFlag_ = false;
		}
	}
}
