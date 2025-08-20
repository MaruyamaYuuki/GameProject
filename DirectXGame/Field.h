#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Field {
public:

	Field();

	~Field();

	void Initialize(KamataEngine::Model* model);

	void Update();

	void Draw(KamataEngine::Camera& camera);

private:
	KamataEngine::Model* model_ = nullptr;

	WorldTransformEx worldTransform_;
};
