#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Skydome {
public:

	void Initialize(KamataEngine::Model* model, const float size, KamataEngine::Camera* camera);

	void Update();

	void Draw();

private:
	WorldTransformEx worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* model_ = nullptr;

	float size_ = 0.0f;
};
