#define NOMINMAX
#include "Screw.h"
#include <cassert>
#include <numbers>
#include <cmath>
#include "Timer.h"

using namespace KamataEngine;

void Screw::Initialize(Model* model, Input* input) {
	assert(model);
	model_ = model;
	assert(input);
	input_ = input;

	timer_->Initialize();

	worldTransform_.Initialize();
	worldTransform_.translation_.x += 10;


}

void Screw::Update() {

    input_->GetJoystickState(0, state);
    input_->GetJoystickStatePrevious(0, preState);

	ScrewWinding();

	DebugText::GetInstance()->ConsolePrintf("Energy : %f\n", energy_);
	worldTransform_.UpdateMatrix();
}

void Screw::Draw(Camera& camera) {
	model_->Draw(worldTransform_, camera); 
}

void Screw::ScrewWinding() {
	if (timer_->IsScrewStart()) {
		bool isSpacePressed = input_->TriggerKey(DIK_SPACE);
		bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

		if (isSpacePressed || isAButtonPressed) {
			energy_++;

			// 180度（πラジアン）ずつ目標角を更新
			targetRotationX_ += static_cast<float>(std::numbers::pi_v<float>);
		}
	}

	// 回転角を滑らかに補間
	float diff = targetRotationX_ - worldTransform_.rotation_.x;

	// 微小差はスキップ（回転終了判定）
	if (std::abs(diff) > 0.001f) {
		// deltaTime（1フレームの時間）を使ってスムーズ補間
		float delta = rotationSpeed_ * (1.0f / 60.0f); // 毎フレームの回転量
		if (diff > 0.0f) {
			worldTransform_.rotation_.x += std::min(delta, diff);
		} else {
			worldTransform_.rotation_.x += std::max(-delta, diff);
		}
	}
}
