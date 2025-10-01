#pragma once
#include "KamataEngine.h"
#include "../../Engine/Core/WorldTransformEx.h"

class Skydome {
public:

	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3 size, KamataEngine::Camera* camera);

	void Update();

	void Draw();

	// 距離に応じて透明度を変更する
	void UpdateAlphaByDistance(const KamataEngine::Vector3& targetPos);

private:
	WorldTransformEx worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Vector3 size_ = {0.0f, 0.0f, 0.0f};
	float alpha_ = 1.0f;
};
