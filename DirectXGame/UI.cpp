#include "UI.h"
#define MNOMINMAX
#include <algorithm>
#include "Timer.h"
#include "Objects/Rocket.h"
#include "Setting.h"

using namespace KamataEngine;

UI::~UI() {
	delete hundredDigitSprite_;
	delete tenDigitSprite_;
	delete oneDigitSprite_;
	delete meterSprite_;
	delete counterSprite_;
	delete gamePadConfigSprite_;
	delete bestRecordHundredDigitSprite_;
	delete bestRecordTenDigitSprite_;
	delete bestRecordOneDigitSprite_;
	delete bestRecordTextSprite_;
	delete afterSelectSprite_;
	delete newRecordSprite_;
}

void UI::InitializeGameUI(Timer* timer, Rocket* rocket, Setting* setting) { 
	timer_ = timer;
	rocket_ = rocket;
	setting_ = setting;

	//------------------------カウンター-------------------------------
	// 数字テクスチャの読み込み
	for (int i = 0; i < 11; i++) {
		std::string fileName = "numbers/counter/" + std::to_string(i) + ".png";
		counterTextures[i] = TextureManager::Load(fileName.c_str());
	}

	counterSprite_ = Sprite::Create(counterTextures[10], {50.0f, 50.0f});
	//-----------------------------------------------------------------
	
	//----------------------スコア-------------------------------------
	record_ = 0; 
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

	//----------------------最高記録-------------------------------------
	bestRecord_ = 0;
	// 数字テクスチャの読み込み
	for (int i = 0; i < 10; i++) {
		std::string fileName = "numbers/bestRecord/" + std::to_string(i) + ".png";
		bestRecordTextures[i] = TextureManager::Load(fileName.c_str());
	}
	bestRecordTextTexture = TextureManager::Load("numbers/bestRecord/bestRecord.png");

	bestRecordHundredDigitSprite_ = Sprite::Create(bestRecordTextures[0], {50.0f, 50.0f});
	bestRecordTenDigitSprite_ = Sprite::Create(bestRecordTextures[0], {50.0f, 50.0f});
	bestRecordOneDigitSprite_ = Sprite::Create(bestRecordTextures[0], {50.0f, 50.0f});
	bestRecordTextSprite_ = Sprite::Create(bestRecordTextTexture, {50.0f, 50.0f});
	//-------------------------------------------------------------------

	//----------------------リトライかタイトルかの選択-------------------
	afterSelectToRetryTexture = TextureManager::Load("afterSelectToRetry.png");
	afterSelectToTitleTexture = TextureManager::Load("afterSelectToTitle.png");
	newRecordTexture = TextureManager::Load("newRecord.png");

	afterSelectSprite_ = Sprite::Create(afterSelectToRetryTexture, {0.0f, 0.0f});
	newRecordSprite_ = Sprite::Create(newRecordTexture, {0.0f, 0.0f});
	//-------------------------------------------------------------------

}

void UI::InitializeTitleUI(Setting* setting) { 
	setting_ = setting; 

	//----------------------ゲームパッド設定表示-------------------------
	padConfigAButtonTexture = TextureManager::Load("padConfigAButton.png");
	padConfigStickTexture = TextureManager::Load("padConfigStick.png");

	gamePadConfigSprite_ = Sprite::Create(padConfigAButtonTexture, {50.0f, 50.0f});
	//-------------------------------------------------------------------
}

// -----UIの更新-----

void UI::Update() {
	UpdateScore();
	UpdateCounter();
	UpdateBestRecord();
}

void UI::UpdateScore() { 
	record_ = int(rocket_->GetWorldTransform().translation_.y); 

	int one = record_ % 10;
	int ten = (record_ / 10) % 10;
	int hundred = (record_ / 100) % 10;

	hundredDigitSprite_->SetTextureHandle(recordTextures[hundred]);
	tenDigitSprite_->SetTextureHandle(recordTextures[ten]);
	oneDigitSprite_->SetTextureHandle(recordTextures[one]);

	hundredDigitSprite_->SetPosition({565.0f, 550.0f});
	tenDigitSprite_->SetPosition({615.0f, 550.0f});
	oneDigitSprite_->SetPosition({665.0f, 550.0f});
	meterSprite_->SetPosition({720.0f, 555.0f});

	if (rocket_->IsDrawRecords()) {
		if (recordSpriteAlpha_ < 1.0f) {
			recordSpriteAlpha_ += fadeSpeed_;
			if (recordSpriteAlpha_ > 1.0f) {
				recordSpriteAlpha_ = 1.0f; // 負値にならないように固定
			}
		}
	}
}

void UI::UpdateCounter() { 
	int num = int(timer_->GetScrewTime());

	if (num < 0) {
		num = 0;
	}

	DebugText::GetInstance()->ConsolePrintf("ScrewTime : %d\n", num);

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

void UI::UpdateBestRecord() { 
	bestRecord_ = int(setting_->bestRecord_); 

	int one = bestRecord_ % 10;
	int ten = (bestRecord_ / 10) % 10;
	int hundred = (bestRecord_ / 100) % 10;

	bestRecordHundredDigitSprite_->SetTextureHandle(bestRecordTextures[hundred]);
	bestRecordTenDigitSprite_->SetTextureHandle(bestRecordTextures[ten]);
	bestRecordOneDigitSprite_->SetTextureHandle(bestRecordTextures[one]);

	bestRecordHundredDigitSprite_->SetPosition({10.0f, 20.0f});
	bestRecordTenDigitSprite_->SetPosition({60.0f, 20.0f});
	bestRecordOneDigitSprite_->SetPosition({110.0f, 20.0f});
	bestRecordTextSprite_->SetPosition({10.0f, 10.0f});

	if (rocket_->IsDrawRecords()) {
		if (bestRecordSpriteAlpha_ < 1.0f) {
			bestRecordSpriteAlpha_ += fadeSpeed_;
			if (bestRecordSpriteAlpha_ > 1.0f) {
				bestRecordSpriteAlpha_ = 1.0f; // 負値にならないように固定
			}
		}
	}
}

void UI::UpdateGamePadConfig() {
	gamePadConfigSprite_->SetPosition({250.0f, 150.0f});
	if (setting_->screwInputType_ == "AButton") {
		gamePadConfigSprite_->SetTextureHandle(padConfigAButtonTexture);
	} else if (setting_->screwInputType_ == "Stick") {
		gamePadConfigSprite_->SetTextureHandle(padConfigStickTexture);
	}
}

void UI::UpdateAfterSelect(int selectNum) {
	if (selectNum == 1) {
		afterSelectSprite_->SetTextureHandle(afterSelectToRetryTexture);
	} else if (selectNum == 2) {
		afterSelectSprite_->SetTextureHandle(afterSelectToTitleTexture);
	}
}

// -----UIの描画-----

void UI::Draw() { 
    DrawScore();
	DrawCounter();
	DrawBestRecord();
	DrawAfterSelect();
 }

void UI::DrawScore() {
	if (rocket_->IsDrawRecords()) {
		hundredDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, recordSpriteAlpha_});
        hundredDigitSprite_->Draw();
		tenDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, recordSpriteAlpha_});
        tenDigitSprite_->Draw();
		oneDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, recordSpriteAlpha_});
        oneDigitSprite_->Draw();
		meterSprite_->SetColor({1.0f, 1.0f, 1.0f, recordSpriteAlpha_});
    	meterSprite_->Draw();
	}
}

void UI::DrawCounter() { 
	if (timer_->IsScrewStart()) {
    	counterSprite_->SetColor({1.0f, 1.0f, 1.0f, counterSpriteAlpha_});
        counterSprite_->Draw();
	}
}

void UI::DrawBestRecord() {
	if (rocket_->IsDrawRecords()) {
		bestRecordHundredDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, bestRecordSpriteAlpha_});
		bestRecordHundredDigitSprite_->Draw();
		bestRecordTenDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, bestRecordSpriteAlpha_});
		bestRecordTenDigitSprite_->Draw();
		bestRecordOneDigitSprite_->SetColor({1.0f, 1.0f, 1.0f, bestRecordSpriteAlpha_});
		bestRecordOneDigitSprite_->Draw();
		bestRecordTextSprite_->SetColor({1.0f, 1.0f, 1.0f, bestRecordSpriteAlpha_});
		bestRecordTextSprite_->Draw();
	}
}

void UI::DrawGamePadConfig() { 
	gamePadConfigSprite_->Draw(); 
}

void UI::DrawAfterSelect() {
	if (rocket_->IsArrived()) {
    	afterSelectSprite_->Draw();
    	if (setting_->bestRecord_ < rocket_->GetRecord()) {
    		newRecordSprite_->Draw();
    	}
	}

}

void UI::Reset() {
	record_ = 0;
	bestRecord_ = 0;
	recordSpriteAlpha_ = 0.0f;
	bestRecordSpriteAlpha_ = 1.0f;
	counterSpriteAlpha_ = 1.0f;
}


