#include "Setting.h"
#include <fstream>

void Setting::Save() {
	nlohmann::json j;
	j["BestRecord"] = bestRecord_;
	j["ScrewInputType"] = screwInputType_;

	std::ofstream ofs(filePath_);
	if (!ofs.is_open()) {
		ofs << j.dump(4);
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
