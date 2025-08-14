#define NOMINMAX
#include "Screw.h"
#include <cassert>
#include <numbers>
#include <cmath>
#include "Timer.h"
#include <algorithm>

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

void Screw::Initialize(Model* model, Input* input, Timer* timer) {
	assert(model);
	model_ = model;
	assert(input);
	input_ = input;
	assert(timer);
	this->timer_ = timer;

	worldTransform_.Initialize();
	worldTransform_.translation_.x += 1;


}

void Screw::Update() {

    input_->GetJoystickState(0, state);
    input_->GetJoystickStatePrevious(0, preState);

	if (input_->TriggerKey(DIK_T) || (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
		if (screwType_ == ScrewType::Button) {
			screwType_ = ScrewType::Joystick;
		} else if (screwType_ == ScrewType::Joystick) {
			screwType_ = ScrewType::Button;
		}
	}

	ScrewWinding();

	DebugText::GetInstance()->ConsolePrintf("Energy : %f\n", energy_);
	worldTransform_.UpdateMatrix();
}

void Screw::Draw(Camera& camera) {
	model_->Draw(worldTransform_, camera); 
}

void Screw::InitializeOnlyModel(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_.x += 1;
}

void Screw::ScrewWinding() {
	// ネジ開始タイミングでのみ処理
	if (!timer_->IsScrewStart())
		return;

	float deltaAngle = 0.0f; // 角度差を格納する変数

	if (screwType_ == ScrewType::Button) {
		// --- ボタン式の処理 ---

		bool isSpacePressed = input_->TriggerKey(DIK_SPACE);
		bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

		if (isSpacePressed || isAButtonPressed) {
			energy_++;
			targetRotationX_ += std::numbers::pi_v<float>; // 180度ずつ回転
		}

		// 回転差を算出してスムーズに追従させる
		deltaAngle = targetRotationX_ - worldTransform_.rotation_.x;

		if (std::abs(deltaAngle) > 0.001f) {
			float delta = rotationSpeed_ * (1.0f / 60.0f); // 1フレームの回転量
			worldTransform_.rotation_.x += std::clamp(deltaAngle, -delta, delta);
		}
	} else if (screwType_ == ScrewType::Joystick) {
		// --- ジョイスティック式の処理 ---

		float x = static_cast<float>(state.Gamepad.sThumbRX);
		float y = static_cast<float>(state.Gamepad.sThumbRY);

		// 微小な入力は無視
		if (std::abs(x) < 10000 && std::abs(y) < 10000)
			return;

		float normX = x / 32768.0f;
		float normY = y / 32768.0f;
		float currentAngle = std::atan2(normY, normX);

		deltaAngle = currentAngle - previousStickAngle_;

		// ラジアン差の正規化
		if (deltaAngle > std::numbers::pi_v<float>)
			deltaAngle -= 2.0f * std::numbers::pi_v<float>;
		if (deltaAngle < -std::numbers::pi_v<float>)
			deltaAngle += 2.0f * std::numbers::pi_v<float>;

		// エネルギー加算
		accumulatedAngle_ += deltaAngle;
		const float stepAngle = std::numbers::pi_v<float>;

		if (std::abs(accumulatedAngle_) >= stepAngle) {
			int steps = static_cast<int>(accumulatedAngle_ / stepAngle);
			energy_ += std::abs(steps);
			accumulatedAngle_ -= steps * stepAngle;
		}

		// ネジを回転（視覚エフェクト）
		worldTransform_.rotation_.x -= deltaAngle;

		// 角度保存
		previousStickAngle_ = currentAngle;
	}
}

void Screw::FollowRocket(const WorldTransformEx& rocketTransform) {
	// ロケット座標にオフセットを足して完全同期
	worldTransform_.translation_ = rocketTransform.translation_ + offsetFromRocket_;
}

void Screw::UpdateDuringFlight(float progress, float rocketSpeed) {
	// 飛行していないときは何もしない
	if (rocketSpeed <= 0.0f) {
		return;
	}

	// progress: 0.0 → 発射直後, 1.0 → 停止直前
	// 回転速度係数（停止に近づくと遅くなる）
	float speedFactor = 5.0f - progress; // 0.0で停止、1.0で最大速

	// 「ネジを回した方向」と逆方向に回転
	// screwType_ によって回転方向を判断
	float direction = (screwType_ == ScrewType::Button) ? -1.0f : 1.0f;
	// 例：回転スピード定数
	float rotationSpeedOnFlight = 2.0f; // ラジアン毎秒

	worldTransform_.rotation_.x += direction * rotationSpeedOnFlight * speedFactor * (1.0f / 60.0f);
}
