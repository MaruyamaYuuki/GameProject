#include "Rocket.h"
#include <cassert>

using namespace KamataEngine;

void Rocket::Initialize(Model* model, Input* input) {
	assert(model);
	model_ = model;

	assert(input);
	input_ = input;

	worldTrandform_.Initialize();
}

void Rocket::Update() {}

void Rocket::Draw() {}
