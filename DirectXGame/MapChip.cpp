#include "MapChip.h"
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace KamataEngine;

MapChip::~MapChip() {}

MapChip::MapChip() {}


std::map<std::string, MapChipType> mapChipTable = {
	{"0", MapChipType::kblank},
    {"1", MapChipType::kWall},
    {"2", MapChipType::kBox},
    {"3", MapChipType::kBrokenBox},
    {"4", MapChipType::kPlug},
    {"5", MapChipType::kDoor},
    {"6", MapChipType::kDoorVertical},
    {"7", MapChipType::kPlayerPos},
    {"8", MapChipType::kGoal},
    {"9", MapChipType::kArtillery},
    {"a", MapChipType::kBoxSwitch},
};

void MapChip::ResetMapChipData() { 
	mapChipData_.data.clear(); 
	mapChipData_.data.resize(kMapWidth);
	for (std::vector<MapChipType>& mapChipDateLine : mapChipData_.data) {
		mapChipDateLine.resize(kMapWidth);
	}
}

void MapChip::LordCSV(const std::string& filePath) { 
	
	ResetMapChipData();

	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapchipCsv;
	mapchipCsv << file.rdbuf();
	file.close();

	for (uint32_t i = 0; i < kMapWidth; i++) {
		std::string line;
		
		getline(mapchipCsv, line);
		
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kMapHeight; j++) {
			std::string word;
			getline(line_stream, word,',');

			if (mapChipTable.contains(word)) {
				mapChipData_.data[i][j] = mapChipTable[word];
			}
		}
	}


}

MapChipType MapChip::GetMapChipTpeByIndex(uint32_t xIndex, uint32_t yIndex) { 
	if (xIndex < 0 || xIndex > kMapWidth - 1) {
		return MapChipType::kblank;
	}
	if (yIndex < 0 || yIndex > kMapHeight - 1) {
		return MapChipType::kblank;
	}

	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChip::GetMapChipPosition(uint32_t xIndex, uint32_t yIndex) { 
	return Vector3(kBlockWidth * xIndex, kBlockHeight * (kMapHeight - 1 - yIndex), 0); 
}
