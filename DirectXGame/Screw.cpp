#include "Screw.h"
#include <cassert>
#include <numbers>
#include "Timer.h"

using namespace KamataEngine;

void Screw::Initialize(Model* model, Input* input, Timer* timer) {
	assert(model);
	model_ = model;
	assert(input);
	input_ = input;
	assert(timer);
	this->timer_ = timer;

	worldTransform_.Initialize();
	worldTransform_.translation_.x += 10;


}

void Screw::Update() {

    input_->GetJoystickState(0, state);
    input_->GetJoystickStatePrevious(0, preState);

	ScrewWinding();

	DebugText::GetInstance()->ConsolePrintf("Enegy : %f\n", energy_);

	worldTransform_.UpdateMatrix();
}

void Screw::Draw(Camera& camera) {
	model_->Draw(worldTransform_, camera); 
}

void Screw::ScrewWinding() {
	if (timer_->IsScrewStart()) {

		if (input_->TriggerKey(DIK_SPACE) || 
			(state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			energy_++;
		}
	}
}
