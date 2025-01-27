#pragma once
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "3d/Camera.h"
#include "makeMath.h"

enum class MapChipType { 
	kblank,//空白
	kWall,//壁
	kBox,//ハコ
	kBrokenBox, //壊せる箱
	// プレイヤーの初期地点
	
	// 大砲、スイッチ、ゴール地点など入れれる
	kPlug,
	kGate,
};

struct MapChipData{
	std::vector<std::vector<MapChipType>> data;
};

class MapChip{
public:
	MapChip();
	~MapChip();

	void ResetMapChipData(); 
	void LordCSV(const std::string& filePath);
	MapChipType GetMapChipTpeByIndex(uint32_t xIndex, uint32_t yIndex);
	KamataEngine::Vector3 GetMapChipPosition(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumVirtical() { return kMapWight; }
	uint32_t GetNumHorizontal() { return kMapHeight; }

	float GetBlockWight() { return kBlockWight; }
	float GetBlockHeight() { return kBlockHeight; }

private:

	KamataEngine::Model* model_;

	const uint32_t kMapWight = 12;
	const uint32_t kMapHeight = 12;

	const float kBlockWight = 2.0f;
	const float kBlockHeight = 2.0f;

	MapChipData mapChipData_;

};