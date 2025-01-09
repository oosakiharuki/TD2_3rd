#pragma once
#include <KamataEngine.h>
#include "MapChip.h"
#include "AABB.h"
#include "Box.h"
#include "BrokenBox.h"
#include "Player.h"
#include "Rope.h"

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

	Model* modelPlayer_ = nullptr;
	Model* modelCarryRope_ = nullptr;
	Model* modelHopRope_ = nullptr;

	MapChip* mapchip_ = nullptr;

	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	Vector3 playerPosition[2]{
	    {-2.0f, 3.0f, 0.0f},
        {2.0f, 3.0f, 0.0f}
    };

	Rope* rope_ = nullptr;
};