#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();
}

void TitleScene::Update() {}

void TitleScene::Draw() {}
