#pragma once
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "3d/Camera.h"
#include "makeMath.h"
#include "AABB.h"

enum class MapChipType {
	kblank,        // 空白
	kWall,         // 壁
	kBox,          // ハコ
	kBrokenBox,    // 壊せる箱
	kPlug,         // electrical
	kDoor,         // ドアゲート横
	kDoorVertical, // ドアゲート縦
	kPlayerPos,    // プレイヤーの初期地点
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

	uint32_t GetNumVirtical() { return kMapWidth; }
	uint32_t GetNumHorizontal() { return kMapHeight; }

	float GetBlockWight() { return kBlockWidth; }
	float GetBlockHeight() { return kBlockHeight; }

	//IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	AABB GetAABB(uint32_t xIndex, uint32_t yIndex);

private:

	KamataEngine::Model* model_;

	const uint32_t kMapWidth = 30;
	const uint32_t kMapHeight = 30;

	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	MapChipData mapChipData_;

};