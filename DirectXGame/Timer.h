#pragma once

class Timer {
public:
	enum class FiringState {
		Standby,
		ReadyToFire,
		Firing,
	};

public:
	void Initialize();

	void Update();

	void Draw();

	void ScrewTimer(bool isFlag);

	void FiringCountTimer(bool isFlag);

	void Reset();

	FiringState GetFiringState() const { return firingState_; }

	bool IsScrewStart() { return isScrewStart; }

	bool IsFiring() { return isFiring; }

	bool IsZoomOut() { return isZoomOut; }

private:

	const float deltaTime = 1.0f / 60.0f;

	float screwTime = 10.0f; // 10秒

	float firingTime = 3.0f; // 3秒

	FiringState firingState_ = FiringState::Standby;

	bool isScrewStart = false;

	bool isFiring = false;

	bool isCountStart = false;

	bool isZoomOut = false;
};
