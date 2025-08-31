#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Particle {
public:
	WorldTransformEx worldTransform_;
	KamataEngine::Vector3 velocity_;
	int lifetime_;
	int initialLifetime_;
	bool isAlive_;
};

class ParticleManager {
public:
	void Initialize(KamataEngine::Model* model);

	// パーティクル生成
	void Emit(KamataEngine::Vector3& pos, KamataEngine::Vector3& vel, int lifetime);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

private:
	KamataEngine::Model* model_ = nullptr;

    std::vector<std::unique_ptr<Particle>> particles_;
};
