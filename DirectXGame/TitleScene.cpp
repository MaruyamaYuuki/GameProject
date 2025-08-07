#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();

	camera_.Initialize();

}

void TitleScene::Update() {
	bool isSpacePressed = input->TriggerKey(DIK_SPACE);
	bool isAButtonPressed = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

	if (isSpacePressed || isAButtonPressed) {
		isFinished_ = true;
	}
}

void TitleScene::Draw() {
	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画後処理
	Sprite::PostDraw();
	dxCommon->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}
