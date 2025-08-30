#pragma once
#include "KamataEngine.h"
#include "WorldTransformEx.h"

class Timer;
class Rocket;
class Setting;
class UI {
public:

	~UI();

	void InitializeGameUI(Timer* timer, Rocket* rocket, Setting* setting);

	void InitializeTitleUI(Setting* setting);

	void Update();

	void UpdateScrewWait();

	void UpdateScore();

	void UpdateCounter();

	void UpdateBestRecord();

	void UpdateGamePadConfig();
	
	void UpdateAfterSelect(int selectNum);

	void Draw();

	void DrawScrewWait();

	void DrawScore();

	void DrawCounter();

	void DrawBestRecord();

	void DrawGamePadConfig();

	void DrawAfterSelect();

	void Reset();

private:
	WorldTransformEx worldTransform_;
	Timer* timer_ = nullptr;
	Rocket* rocket_ = nullptr;
	Setting* setting_ = nullptr;

	int record_ = 0;
	int bestRecord_ = 0;

	KamataEngine::Sprite* screwStartSprite_ = nullptr;
	KamataEngine::Sprite* oneDigitSprite_ = nullptr;
	KamataEngine::Sprite* tenDigitSprite_ = nullptr;
	KamataEngine::Sprite* hundredDigitSprite_ = nullptr;
	KamataEngine::Sprite* meterSprite_ = nullptr;
	KamataEngine::Sprite* counterSprite_ = nullptr;
	KamataEngine::Sprite* bestRecordOneDigitSprite_ = nullptr;
	KamataEngine::Sprite* bestRecordHundredDigitSprite_ = nullptr;
	KamataEngine::Sprite* bestRecordTenDigitSprite_ = nullptr;
	KamataEngine::Sprite* bestRecordTextSprite_ = nullptr;
	KamataEngine::Sprite* gamePadConfigSprite_ = nullptr;
	KamataEngine::Sprite* afterSelectSprite_ = nullptr;
	KamataEngine::Sprite* newRecordSprite_ = nullptr;

	uint32_t screwStartTexture = 0;
	uint32_t recordTextures[10];
	uint32_t meterTexture = 0;
	uint32_t counterTextures[11];
	uint32_t bestRecordTextures[10];
	uint32_t bestRecordTextTexture = 0;
	uint32_t padConfigAButtonTexture = 0;
	uint32_t padConfigStickTexture = 0;
	uint32_t afterSelectToRetryTexture = 0;
	uint32_t afterSelectToTitleTexture = 0;
	uint32_t newRecordTexture = 0;

    // スプライトの透明度(初期値: 不透明)
	float screwStartAlpha_ = 0.5f;
	float recordSpriteAlpha_ = 0.0f; 
	float bestRecordSpriteAlpha_ = 0.0f;
	float counterSpriteAlpha_ = 1.0f;
	float fadeSpeed_ = 0.05f;  // フェードアウト速度
};
