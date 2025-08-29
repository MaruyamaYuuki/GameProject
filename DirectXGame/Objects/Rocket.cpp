#define NOMINMAX
#include "Rocket.h"
#include "Screw.h"
#include "../Timer.h"
#include "../Setting.h"
#include <cassert>
#include <algorithm>

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

void Rocket::Initialize(Model* model, Input* input, Screw* screw, Timer* timer, Setting* setting) {
	assert(model);
	model_ = model;
	assert(input);
	input_ = input;
	assert(screw);
	this->screw_ = screw;
	assert(timer);
	this->timer_ = timer;
	assert(setting);
	this->setting_ = setting;

	worldTransform_.Initialize();

	isFiring_ = false;
	isDrawBestRecord_ = false;
	isArrived = false;
	velocity_.y = 0;
	screwCount_ = 0;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Rocket::Update() { 
	Firing();
	DebugText::GetInstance()->ConsolePrintf("FiringDistance : %f\nTimerStart : %d\n", firingDistance_, isTimerStart_);

	worldTransform_.UpdateMatrix(); 

}

void Rocket::Draw(Camera& camera) { 
	model_->Draw(worldTransform_, camera); 
}

void Rocket::InitializeOnlyModel(KamataEngine::Model* model) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
}

void Rocket::UpdateOnlyModel() { worldTransform_.UpdateMatrix(); }

void Rocket::Firing() {
	screwCount_ = screw_->GetEnergy();

	// 定数（調整用）
	const float minSpeed = 0.1f; // 初速の下限
	const float vMax = 3.5f;    // 最大速度
	const float distancePerScrew = 8.0f;

	if (timer_->GetFiringState() == Timer::FiringState::ReadyToFire) {
		// ネジを巻いた回数に応じて距離を決定
		firingDistance_ = std::min(screwCount_ * distancePerScrew, maxFiringDistance_);

		isFiring_ = true;
		isDrawRecords_ = true;
		velocity_.y = 0;

		//timer_->Reset();
	}

	if (isFiring_) {
		// 高度に応じた進行率
		float progress = worldTransform_.translation_.y / firingDistance_;
		progress = std::clamp(progress, 0.0f, 1.0f);

		// 最小速度保証付きの放物線的な動き
		velocity_.y = minSpeed + (vMax - minSpeed) * std::sin((1.0f - progress) * 3.14159f);

		// 上昇
		worldTransform_.translation_.y += velocity_.y;

		// 飛びすぎ防止
		if (worldTransform_.translation_.y >= firingDistance_) {
			worldTransform_.translation_.y = firingDistance_;
			isFiring_ = false;
			isTimerStart_ = true;
		}
		//Move();
	}
	if (waitingTime_ > 0 && isTimerStart_) {
		waitingTime_--;
	} else if(waitingTime_<=0){
		isArrived = true;
	}
}

void Rocket::Move() {
	// 左右移動の処理
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	XInputGetState(0, &state);

	bool isDPadRPress = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	bool isDPadLPress = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);

    // 左右移動などの処理
	if (input_->PushKey(DIK_A) || isDPadLPress) {
		worldTransform_.translation_.x -= velocity_.x;
	}
	if (input_->PushKey(DIK_D) || isDPadRPress) {
		worldTransform_.translation_.x += velocity_.x;
	}

	// ジョイスティック
	if (input_->GetJoystickState(0, state)) {
		float lx = state.Gamepad.sThumbLX;
		const int DEADZONE = 8000;
		if (lx < -DEADZONE) {
			worldTransform_.translation_.x -= velocity_.x;
		}
		if (lx > DEADZONE) {
			worldTransform_.translation_.x += velocity_.x;
		}
	}

	// 移動範囲を制限
	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -20.0f, 20.0f);
}

void Rocket::Reset() {
	setting_->UpdateBestRecord(firingDistance_);
	isFiring_ = false;
	isDrawRecords_ = false;
	isArrived = false;
	velocity_.y = 0;
	screwCount_ = 0;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	firingDistance_ = 0;
}
