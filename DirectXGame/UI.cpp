#include "UI.h"
#define MNOMINMAX
#include <algorithm>
#include "Timer.h"
#include "Objects/Rocket.h"

using namespace KamataEngine;

UI::~UI() {
	delete hundredDigitSprite_;
	delete tenDigitSprite_;
	delete oneDigitSprite_;
	delete meterSprite_;
}

void UI::Initialize(Timer* timer, Rocket* rocket) { 
	timer_ = timer;
	rocket_ = rocket;

	//------------------------カウンター-------------------------------
	// 数字テクスチャの読み込み
	for (int i = 0; i < 11; i++) {
		std::string fileName = "numbers/counter/" + std::to_string(i) + ".png";
		counterTextures[i] = TextureManager::Load(fileName.c_str());
	}

	counterSprite_ = Sprite::Create(counterTextures[10], {50.0f, 50.0f});
	//-----------------------------------------------------------------
	
	//----------------------スコア-------------------------------------
	score_ = 0; 
	// 数字テクスチャの読み込み
	for (int i = 0; i < 10; i++) {
		std::string fileName = "numbers/record/" + std::to_string(i) + ".png";
		recordTextures[i] = TextureManager::Load(fileName.c_str());
	}

	meterTexture = TextureManager::Load("numbers/record/meter.png");

	hundredDigitSprite_ = Sprite::Create(recordTextures[0], {50.0f, 50.0f});
	tenDigitSprite_ = Sprite::Create(recordTextures[0], {50.0f, 50.0f});
	oneDigitSprite_ = Sprite::Create(recordTextures[0], {50.0f, 50.0f});
	meterSprite_ = Sprite::Create(meterTexture, {50.0f, 50.0f});
	//-------------------------------------------------------------------

}

void UI::Update() {
	UpdateScore();
	UpdateCounter();
}

void UI::Draw() { 
    DrawScore();
	DrawCounter();
 }

void UI::UpdateScore() { 
	score_ = int(rocket_->GetWorldTransform().translation_.y); 

	int one = score_ % 10;
	int ten = (score_ / 10) % 10;
	int hundred = (score_ / 100) % 10;

	hundredDigitSprite_->SetTextureHandle(recordTextures[hundred]);
	tenDigitSprite_->SetTextureHandle(recordTextures[ten]);
	oneDigitSprite_->SetTextureHandle(recordTextures[one]);

	hundredDigitSprite_->SetPosition({565.0f, 550.0f});
	tenDigitSprite_->SetPosition({615.0f, 550.0f});
	oneDigitSprite_->SetPosition({665.0f, 550.0f});
	meterSprite_->SetPosition({720.0f, 555.0f});

	if (rocket_->IsFiring()) {
		if (scoreSpriteAlpha_ < 1.0f) {
			scoreSpriteAlpha_ += fadeSpeed_;
			if (scoreSpriteAlpha_ > 1.0f) {
				scoreSpriteAlpha_ = 1.0f; // 負値にならないように固定
			}
		}
	}
}

void UI::DrawScore() {
	if (rocket_->IsFiring()) {
		hundredDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, scoreSpriteAlpha_});
        hundredDigitSprite_->Draw();
		tenDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, scoreSpriteAlpha_});
        tenDigitSprite_->Draw();
		oneDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, scoreSpriteAlpha_});
        oneDigitSprite_->Draw();
		meterSprite_->SetColor({1.0f, 1.0f, 1.0f, scoreSpriteAlpha_});
    	meterSprite_->Draw();
	}
}

void UI::UpdateCounter() { 
	int num = int(timer_->GetScrewTime());

	counterSprite_->SetPosition({590.0f, 100.0f});
	counterSprite_->SetTextureHandle(counterTextures[num]);

	if (num == 0) {
		if (counterSpriteAlpha_ > 0.0f) {
			counterSpriteAlpha_ -= fadeSpeed_;
			if (counterSpriteAlpha_ < 0.0f) {
				counterSpriteAlpha_ = 0.0f; // 負値にならないように固定
			}
		}
	}
}

void UI::DrawCounter() { 
	if (timer_->IsScrewStart()) {
    	counterSprite_->SetColor({1.0f, 1.0f, 1.0f, counterSpriteAlpha_});
        counterSprite_->Draw();
	}

}
