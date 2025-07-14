#include "Timer.h"

void Timer::Initialize() {
	screwTime = 600.0f; // 10秒

	firingTime = 180.0f; // 3秒

	isScrewStart = false;

	isFiring = false;

	isCountStart = false;
}

void Timer::Update() {}

void Timer::Draw() {}

void Timer::ScrewTimer(bool isFlag) {
	if (screwTime >= 0.0f && isFlag) {
		screwTime -= deltaTime;
		isScrewStart = true;
	} else {
		isScrewStart = false;
	}
}

void Timer::FiringCountTimer(bool isFlag) {
	if (firingTime >= 0.0f && isFlag) {
		firingTime -= deltaTime;
		isFiring = true;
	}
}

void Timer::Reset() {

	screwTime = 600.0f; // 10秒

	firingTime = 180.0f; // 3秒

	isScrewStart = false;

	isFiring = false;

	isCountStart = false;
}
