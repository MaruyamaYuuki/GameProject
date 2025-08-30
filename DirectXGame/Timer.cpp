#include "Timer.h"
#include "KamataEngine.h"

using namespace KamataEngine;

void Timer::Initialize() {
	screwWait = 4.0f;
	screwTime = 10.9f; // 10秒
	firingTime = 3.0f; // 3秒

	state_ = State::WaitScrew;
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

void Timer::UpdateWaitScrew() {
	screwWait -= deltaTime;
	if (screwWait <= 0) {
		screwWait = 0;
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
