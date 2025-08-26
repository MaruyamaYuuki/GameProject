#pragma once
#include "KamataEngine.h"

class Rocket;
class CameraController {
public:
	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

public:

	void Initialize();

	void Update();

	void SetTarget(Rocket* rocket) { target_ = rocket; }

	const KamataEngine::Camera& GetCamera() const { return camera_; }

	void Reset();

	void SetMoveableArea(Rect area) { moveableArea_ = area; }

	bool CameraZoomOuted() {
		if (targetOffset_.z <= zoomOutDistance_.z) {
			return true;
		} else {
			return false;
		}
	}

	// Vector3での線形補間
	KamataEngine::Vector3 Vector3Lerp(const KamataEngine::Vector3& start, const KamataEngine::Vector3& end, float t);

private:
	KamataEngine::Camera camera_;
	Rocket* target_ = nullptr;
	// 追従対象のカメラの座標の差（オフセット）
	KamataEngine::Vector3 targetOffset_ = {0, 0, -20.0f};
	// ズームアウト後のカメラの距離
	KamataEngine::Vector3 zoomOutDistance_ = {0, 0, -40.0f};
	static inline const float kOffsetLerpRate = 0.05f;
	// カメラ移動範囲
	Rect moveableArea_ = {0, 100, 0, 100};
	// カメラの目標座標
	KamataEngine::Vector3 goalPos;
	// 座標補間割合
	static inline const float kInterpolationRate = 1.5f;
	// 速度掛け率
	static inline const float kVelocityBias = 30.0f;
	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect kMargin = {-5.0f, 5.0f, -4.0f, 4.0f};
};
