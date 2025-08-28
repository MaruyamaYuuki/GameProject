#pragma once
#include <string>
#include <json.hpp>

class Setting {
public:
	// 保存する内容
	float bestRecord_ = 0.0f;
	std::string screwInputType_ = "AButton";

	// コンストラクタでロード
	Setting(const std::string& filePath = "Resources/Config.json") 
		: filePath_(filePath) 
	{ 
		Load(); 
	}

	// 設定の保存
	void Save();

	// 設定の読み込み
	void Load();

	// 最高記録の更新
	void UpdateBestRecord(float newRecord);

private:
	std::string filePath_;
};
