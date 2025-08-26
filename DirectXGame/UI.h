#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Timer;
class UI {
public:

	~UI();

	void Initialize(Timer* timer);

	void Update();

	void Draw();

	void UpdateScore(float score);

	void DrawScore();

private:
	WorldTransformEx worldTransform_;
	Timer* timer_ = nullptr;

	int score_ = 0;

	KamataEngine::Sprite* oneDigitSprite_ = nullptr;
	KamataEngine::Sprite* tenDigitSprite_ = nullptr;
	KamataEngine::Sprite* hundredDigitSprite_ = nullptr;
	KamataEngine::Sprite* meterSprite_ = nullptr;

	uint32_t numberTextures[10];
	uint32_t meterTexture = 0;
};
