#pragma once
#include <KamataEngine.h>
#include "MapChip.h"
#include "AABB.h"
#include "Box.h"
#include "BrokenBox.h"
#include "Gate.h"

using namespace KamataEngine;

class GameScene {

public:
	// ゲームシーン

	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	Camera viewProjection_;
	uint32_t texture = 0;

	std::vector<std::vector<KamataEngine::WorldTransform*>> blocks_;
	std::list<Box*> boxes;
	
	std::list<Gate*> gates;
	std::list<Gate*> gatesList[2];
	bool isGate = false;
	bool isA = false;

	MapChip* mapchip_ = nullptr;
	//Box* box_ = nullptr;
};