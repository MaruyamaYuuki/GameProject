#include "Skydome.h"
#include <cassert>

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

void Skydome::Initialize(Model* model, const Vector3 size, KamataEngine::Camera* camera) {
	assert(model);
	model_ = model;
	assert(camera);
	camera_ = camera;

	size_ = size;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {size_};
}

void Skydome::Update() { 
	worldTransform_.UpdateMatrix(); 
}

void Skydome::Draw() { 
	model_->SetAlpha(alpha_);
	model_->Draw(worldTransform_, *camera_); 
}

void Skydome::UpdateAlphaByDistance(const Vector3& targetPos) {
	// 球の中心位置（ワールド座標）
	Vector3 domeCenter = worldTransform_.translation_;

	// ロケット（targetPos）との距離
	float dist = Length(targetPos - domeCenter);

	// 球の端（size_が半径のスケールなので、端までの距離はsize_）
	float fadeStart = size_.y * 0.8f; // この距離から薄くなる
	float fadeEnd = size_.y;          // この距離で完全に透明

	// 透明度を補間
	if (dist < fadeStart) {
		alpha_ = 1.0f;
	} else if (dist > fadeEnd) {
		alpha_ = 0.0f;
	} else {
		float t = (dist - fadeStart) / (fadeEnd - fadeStart);
		alpha_ = 1.0f - t;
	}
}
