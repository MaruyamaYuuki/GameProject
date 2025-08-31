#include "Field.h"
#include <cassert>

using namespace KamataEngine;

Field::Field() {}

Field::~Field() {}

void Field::Initialize(Model* model) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_.y -= 1.5f;

}

void Field::Update() { 
	worldTransform_.UpdateMatrix(); 
}

void Field::Draw(Camera& camera) { 
	model_->Draw(worldTransform_, camera); 
}
