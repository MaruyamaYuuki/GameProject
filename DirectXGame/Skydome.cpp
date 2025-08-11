#include "Skydome.h"
#include <cassert>

using namespace KamataEngine;

void Skydome::Initialize(Model* model, const float size, KamataEngine::Camera* camera) {
	assert(model);
	model_ = model;
	assert(camera);
	camera_ = camera;

	size_ = size;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {size, size, 1.0f};
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw() { model_->Draw(worldTransform_, *camera_); }
