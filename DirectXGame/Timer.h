#pragma once

class Timer {
public:
	void Initialize();

	void Update();

	void Draw();

	void ScrewTimer(bool isFlag);

	void FiringCountTimer(bool isFlag);

	void Reset();

	bool IsScrewStart() { return isScrewStart; }

	bool IsFiring() { return isFiring; }

private:

	const float deltaTime = 1.0f / 60.0f;

	float screwTime = 10.0f; // 10秒

	float firingTime = 3.0f; // 3秒

	bool isScrewStart = false;

	bool isFiring = false;

	bool isCountStart = false;
};
