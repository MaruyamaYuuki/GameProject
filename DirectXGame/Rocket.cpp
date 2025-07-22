#define NOMINMAX
#include "Rocket.h"
#include "Screw.h"
#include "Timer.h"
#include <cassert>
#include <algorithm>

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

void Rocket::Initialize(Model* model, Input* input, Screw* screw, Timer* timer) {
	assert(model);
	model_ = model;
	assert(input);
	input_ = input;
	assert(screw);
	this->screw_ = screw;
	assert(timer);
	this->timer_ = timer;

	worldTransform_.Initialize();
}

void Rocket::Update() { 
	Firing();

	DebugText::GetInstance()->ConsolePrintf("FiringDistance : %f\n", firingDistance_);
	DebugText::GetInstance()->ConsolePrintf("Translation : %f\nVelocity.Y : %f", worldTransform_.translation_.y,velocity_.y);

	worldTransform_.UpdateMatrix(); 

}

void Rocket::Draw(Camera& camera) { 
	model_->Draw(worldTransform_, camera); 
}

void Rocket::Firing() {
	screwCount_ = screw_->GetEnergy();

	if (timer_->GetFiringState() == Timer::FiringState::ReadyToFire) {
		// ネジを巻いた回数に応じて距離を決定
		const float distancePerScrew = 80.0f;
		firingDistance_ = std::min(screwCount_ * distancePerScrew, maxFiringDistance_);

		isFiring_ = true;
		velocity_.y = 0;

		timer_->Reset();
	}
	if (isFiring_) {

		// 高度に応じて加減速させるため、割合（進行率）を計算
		float progress = worldTransform_.translation_.y / firingDistance_;
		progress = std::clamp(progress, 0.0f, 1.0f);

		// 放物線的な動きを再現：最初は加速→最後に減速
		// v = vMax * sin((1 - progress) * π)
		const float vMax = 10.0f; // 最大速度
		velocity_.y = vMax * std::sin((1.0f - progress) * 3.14159f);

		// 上昇
		worldTransform_.translation_.y += velocity_.y;

		// 飛びすぎ防止
		if (worldTransform_.translation_.y >= firingDistance_) {
			worldTransform_.translation_.y = firingDistance_;
			isFiring_ = false;
		}
	}
}
