#include "Screw.h"
#include <cassert>
#include <numbers>

using namespace KamataEngine;

void Screw::Initialize(Model* model, Input* input) {
	assert(model);
	model_ = model;
	assert(input);
	input_ = input;

	worldTransfor_.Initialize();
}

void Screw::Update() {
	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);

	ScrewWinding();

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
