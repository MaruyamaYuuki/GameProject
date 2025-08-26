#define NOMINMAX
#include "CameraController.h"
#include "Objects/Rocket.h"
#include <algorithm>

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

void CameraController::Initialize() { 
	camera_.Initialize(); 
}

void CameraController::Update(bool flag) {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	const Vector3& targetVelocity = target_->GetVelocity();

	if (flag) {
		// フラグが立ったらカメラをズームアウト
    	targetOffset_ = Vector3Lerp(targetOffset_, zoomOutDistance_, kOffsetLerpRate);

		// --- 誤差吸収処理 ---
		if (fabs(targetOffset_.z - zoomOutDistance_.z) < 0.01f) {
			targetOffset_.z = zoomOutDistance_.z;
		}
	}


	// 追従対象とオフセットからカメラの目標座標を計算
	goalPos = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;

    // 座標補間によりゆったり追従（YやZだけ補間）
	camera_.translation_.y = Lerp(camera_.translation_.y, goalPos.y, kInterpolationRate);
	camera_.translation_.z = Lerp(camera_.translation_.z, goalPos.z, kInterpolationRate);

	// 追従対象が画面外に出ないように補正
	camera_.translation_.y = std::max(camera_.translation_.y, targetWorldTransform.translation_.y + kMargin.bottom);
	camera_.translation_.y = std::min(camera_.translation_.y, targetWorldTransform.translation_.y + kMargin.top);

	// 行列を更新する
	camera_.UpdateMatrix();

	DebugText::GetInstance()->ConsolePrintf("CameraPoxZ : %f\n", targetOffset_.z);
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	camera_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}

KamataEngine::Vector3 CameraController::Vector3Lerp(const KamataEngine::Vector3& start, const KamataEngine::Vector3& end, float t) { return start + t * (end - start); }
