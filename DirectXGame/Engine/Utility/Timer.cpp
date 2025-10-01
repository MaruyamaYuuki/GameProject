#include "Timer.h"

using namespace KamataEngine;

void Timer::Initialize() {
	audio_ = Audio::GetInstance();

	screwWait = 4.0f;
	screwTime = 10.9f; // 10秒
	firingTime = 3.0f; // 3秒

	state_ = State::WaitScrew;

	waitSEDataHandle_ = audio_->LoadWave("sounds/waitCount.wav");
	bgmDataHandle_ = audio_->LoadWave("sounds/gameBGM.wav");

	waitSEVoiceHandle_ = audio_->PlayWave(waitSEDataHandle_, false, 1.0f);
}

void Timer::Update() {
	switch (state_) {
	case Timer::State::WaitScrew:
		UpdateWaitScrew();
		break;
	case Timer::State::Screw:
		UpdateScrew();
		break;
	case Timer::State::Firing:
		UpdateFiring();
		break;
	}
}

void Timer::Reset() {
	screwWait = 4.0f;
	screwTime = 10.9f; // 10秒
	firingTime = 3.0f; // 3秒
	firingState_ = FiringState::Standby;
}

void Timer::StopBGM() { audio_->StopWave(bgmVoiceHandle_); }

void Timer::PlayWaitCountSE() { waitSEVoiceHandle_ = audio_->PlayWave(waitSEDataHandle_, false, 0.5f); }

void Timer::UpdateWaitScrew() {
	screwWait -= deltaTime;
	if (screwWait <= 0) {
		screwWait = 0;
		bgmVoiceHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.7f);
		state_ = State::Screw;
	}
}

void Timer::UpdateScrew() {
	screwTime -= deltaTime;
	if (screwTime <= 0) {
		screwTime = 0;
		state_ = State::Firing;
	}
}

void Timer::UpdateFiring() {
	firingTime -= deltaTime;
	if (firingTime <= 0) {
		firingTime = 0;
		state_ = State::Finished;
	}
}
