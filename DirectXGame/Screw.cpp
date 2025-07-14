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
	timer_ = timer;

	worldTransfor_.Initialize();
}

void Screw::Update() {
	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);

	ScrewWinding();

	DebugText::GetInstance()->ConsolePrintf("Enegy : %f\n", energy_);

	worldTransfor_.UpdateMatrix();
}

void Screw::Draw() {}

void Screw::ScrewWinding() {
	if (testFlag) {
		if (input_->TriggerKey(DIK_SPACE) || 
			(state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			energy_++;
		}
	}
}
