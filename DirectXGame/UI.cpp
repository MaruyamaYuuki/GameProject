#include "UI.h"
#define MNOMINMAX
#include <algorithm>
#include "Timer.h"

using namespace KamataEngine;

UI::~UI() {
	delete hundredDigitSprite_;
	delete tenDigitSprite_;
	delete oneDigitSprite_;
	delete meterSprite_;
	delete lineSprite_;
}

void UI::Initialize(Timer* timer) { 
	timer_ = timer;

	score_ = 0; 

	//----------------------スコア-------------------------------------
	// 数字テクスチャの読み込み
	for (int i = 0; i < 10; i++) {
		std::string fileName = "scoreNumbers/" + std::to_string(i) + ".png";
		numberTextures[i] = TextureManager::Load(fileName.c_str());
	}

	meterTexture = TextureManager::Load("scoreNumbers/meter.png");

	hundredDigitSprite_ = Sprite::Create(numberTextures[0], {50.0f, 50.0f});
	tenDigitSprite_ = Sprite::Create(numberTextures[0], {50.0f, 50.0f});
	oneDigitSprite_ = Sprite::Create(numberTextures[0], {50.0f, 50.0f});
	meterSprite_ = Sprite::Create(meterTexture, {50.0f, 50.0f});
	//--------------------------------------------------------------------

}

void UI::Update() {}

void UI::Draw() { DrawScore(); }

void UI::UpdateScore(float score) { 
	score_ = int(score); 

	int one = score_ % 10;
	int ten = (score_ / 10) % 10;
	int hundred = (score_ / 100) % 10;

	hundredDigitSprite_->SetTextureHandle(numberTextures[hundred]);
	tenDigitSprite_->SetTextureHandle(numberTextures[ten]);
	oneDigitSprite_->SetTextureHandle(numberTextures[one]);

	hundredDigitSprite_->SetPosition({555.0f, 550.0f});
	tenDigitSprite_->SetPosition({615.0f, 550.0f});
	oneDigitSprite_->SetPosition({675.0f, 550.0f});
	meterSprite_->SetPosition({750.0f, 580.0f});
	lineSprite_->SetPosition({550.0f, 600.0f});
}

void UI::DrawScore() {
	//if (timer_->GetFiringState() == Timer::FiringState::ReadyToFire) {
    	hundredDigitSprite_->Draw();
    	tenDigitSprite_->Draw();
    	oneDigitSprite_->Draw();
		meterSprite_->Draw();
//	}
}
