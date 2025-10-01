#include "Setting.h"
#include <fstream>
#include <iostream>

void Setting::Save() {
	nlohmann::json j;
	j["BestRecord"] = bestRecord_;
	j["ScrewInputType"] = screwInputType_;

	std::ofstream ofs(filePath_);
	if (ofs.is_open()) { // 開けたら書き込む
		ofs << j.dump(4);
	} else {
		// 開けなかった場合のエラーログ
		std::cerr << "Failed to open setting file for saving: " << filePath_ << std::endl;
	}
}


void Setting::Load() {
	std::ifstream ifs(filePath_);
	if (!ifs.is_open())
		return; // ファイルがなければ初期値のまま

	nlohmann::json j;
	ifs >> j;

	if (j.contains("BestRecord"))
		bestRecord_ = j["BestRecord"];
	if (j.contains("ScrewInputType"))
		screwInputType_ = j["ScrewInputType"];
}

void Setting::UpdateBestRecord(float newRecord) {
	if (newRecord > bestRecord_) {
		bestRecord_ = newRecord;
		Save();
	}
}
