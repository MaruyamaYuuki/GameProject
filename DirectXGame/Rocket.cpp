#include "Rocket.h"
#include <cassert>

using namespace KamataEngine;

void Rocket::Initialize(Model* model, Input* input) {
	assert(model);
	model_ = model;

	assert(input);
	input_ = input;

	worldTrandform_.Initialize();
}

void Rocket::Update() { 
	Firing();

	worldTrandform_.UpDateMatrix(); 
}

void Rocket::Draw() {}

void Rocket::Firing() {
	if (testFlag_) {
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
