#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Timer;
class Rocket;
class UI {
public:

	~UI();

	void Initialize(Timer* timer, Rocket* rocket);

	void Update();

	void Draw();

	void UpdateScore();

	void DrawScore();

	void UpdateCounter();

	void DrawCounter();

private:
	WorldTransformEx worldTransform_;
	Timer* timer_ = nullptr;
	Rocket* rocket_ = nullptr;

	int score_ = 0;

	KamataEngine::Sprite* oneDigitSprite_ = nullptr;
	KamataEngine::Sprite* tenDigitSprite_ = nullptr;
	KamataEngine::Sprite* hundredDigitSprite_ = nullptr;
	KamataEngine::Sprite* meterSprite_ = nullptr;

	uint32_t recordTextures[10];
	uint32_t meterTexture = 0;

	KamataEngine::Sprite* counterSprite_ = nullptr;

	uint32_t counterTextures[11];

    // スプライトの透明度(初期値: 不透明)
	float scoreSpriteAlpha_ = 0.0f; 
	float counterSpriteAlpha_ = 1.0f;
	float fadeSpeed_ = 0.05f;  // フェードアウト速度
};
