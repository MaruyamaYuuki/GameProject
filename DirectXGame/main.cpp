#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"


using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"LE3C_24_マルヤマ_ユウキ");
	// DirectXCommonインスタンス
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		gameScene->Update();

		// 描画処理
		dxCommon->PreDraw();

		gameScene->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	delete gameScene;
	gameScene = nullptr;

	// エンジンの終了処理
	KamataEngine::Finalize();
	
	return 0;
}
