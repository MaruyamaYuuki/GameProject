#include "ParticleManager.h"

using namespace KamataEngine;
using namespace KamataEngine::MathUtility;

void ParticleManager::Initialize(Model* model) { model_ = model; }

void ParticleManager::Emit(Vector3& pos, Vector3& vel, int lifetime) {
	Particle p{};
	p.worldTransform_.translation_ = pos;
	p.velocity_ = vel;
	p.lifetime_ = lifetime;
	p.initialLifetime_ = lifetime;
	p.isAlive_ = true;
	p.worldTransform_.Initialize();
	particles_.push_back(std::make_unique<Particle>(p));
}

void ParticleManager::Update() {
	for (auto& p : particles_) {
		if (!p.isAlive_)
			continue;

		// 移動
		p.worldTransform_.translation_ += p.velocity_;

		// 寿命カウント
		p.lifetime_--;
		if (p.lifetime_ <= 0) {
			p.isAlive_ = false;
		}

		p.worldTransform_.UpdateMatrix();
	}
}

void ParticleManager::Draw(Camera& camera) {
	for (auto& p : particles_) {
		if (!p.isAlive_)
			continue;

		// 残り寿命の割合
		float lifeRatio = (float)p.lifetime_ / (float)p.initialLifetime_;

		// 板ポリ描画時にカラーを渡す
		model_->SetAlpha(lifeRatio);
		model_->Draw(p.worldTransform_, camera);
	}
}
