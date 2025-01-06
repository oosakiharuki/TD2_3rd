#pragma once
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "3d/Camera.h"
#include "makeMath.h"

enum class MapChipType { 
	kblank,//空白
	kblock,//ブロック
};

struct MapChipData{
	std::vector<std::vector<MapChipType>> data;
};

class MapChip{
public:
	MapChip();
	~MapChip();
	void Initialize();
	void Update();
	void Draw();

	void ResetMapChipData(); 
	void LordCSV(const std::string& filePath);
	MapChipType GetMapChipTpeByIndex(uint32_t xIndex, uint32_t yIndex);
	KamataEngine::Vector3 GetMapChipPosition(uint32_t xIndex, uint32_t yIndex);

private:

	KamataEngine::Model* model_;

	std::vector<std::vector<KamataEngine::WorldTransform*>> blocks_;
	KamataEngine::Camera ViewProjection_;

	const uint32_t kMapWight = 16;
	const uint32_t kMapHeight = 16;

	const float kBlockWight = 2.0f;
	const float kBlockHeight = 2.0f;

	MapChipData mapChipData_;

};