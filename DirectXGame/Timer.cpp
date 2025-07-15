#include "Timer.h"
#include "KamataEngine.h"

using namespace KamataEngine;

void Timer::Initialize() {
	screwTime = 10.0f; // 10秒

	firingTime = 3.0f; // 3秒

	isScrewStart = false;

	isFiring = false;

	isCountStart = false;
}

void Timer::Update() { DebugText::GetInstance()->ConsolePrintf("ScrewTime : %f\nisScrewStart : %d\n", screwTime, isScrewStart); }

void Timer::Draw() {}

void Timer::ScrewTimer(bool isFlag) {
	if (screwTime >= 0.0f && isFlag) {
		screwTime -= deltaTime;
		isScrewStart = true;
	} else if (screwTime <= 0){
		isScrewStart = false;
	}
}

void Timer::FiringCountTimer(bool isFlag) {
	if (firingTime >= 0.0f && isFlag) {
		firingTime -= deltaTime;
	} else if (firingTime <= 0.0f) {
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
