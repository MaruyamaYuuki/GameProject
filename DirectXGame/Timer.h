#pragma once
#include "KamataEngine.h"

class Timer {
public:
	enum class FiringState {
		Standby,
		ReadyToFire,
		Firing,
	};

	enum class State {
		None,
		WaitScrew,  // ネジ巻き待機
		Screw,      // ネジ巻き中
		Firing,     // 発射カウントダウン
		Finished    // 完了
	};

public:
	void Initialize();

	void Update();

	void Reset();

	float GetScrewWaitTime() const { return screwWait; }

	float GetScrewTime() const { return screwTime; }

	float GetFiringTime() const { return firingTime; }

	State GetTimerState() const { return state_; }

	void SetTimerState(State state) { state_ = state; }

	void StopBGM();

	void PlayWaitCountSE();

private:

	void UpdateWaitScrew();

	void UpdateScrew();

	void UpdateFiring();

private:
	KamataEngine::Audio* audio_ = nullptr;

	const float deltaTime = 1.0f / 60.0f;

	float screwWait = 4.0f;

	float screwTime = 10.0f; // 10秒

	float firingTime = 3.0f; // 3秒

	FiringState firingState_ = FiringState::Standby;

	State state_ = State::None;

	uint32_t waitSEDataHandle_ = 0;
	uint32_t waitSEVoiceHandle_ = 0;
	uint32_t bgmDataHandle_ = 0;
	uint32_t bgmVoiceHandle_ = 0;
};
