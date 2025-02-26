#pragma once
#include <KamataEngine.h>
#include "MapChip.h"
#include "AABB.h"
#include "Box.h"
#include "BrokenBox.h"

#include"Electricity.h"
#include"Electricity2.h"

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

	void CheckAllCollision();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;
	//ギミック用
	Model* modelElectricity1_ = nullptr;
	Model* modelElectricity2_ = nullptr;
	Model* modelWall1_ = nullptr;
	Model* modelWall2_ = nullptr;

	WorldTransform worldTransform_;
	Camera viewProjection_;
	uint32_t texture = 0;

	std::vector<std::vector<KamataEngine::WorldTransform*>> blocks_;
	std::list<Box*> boxes;

	Model* modelPlayer_ = nullptr;
	Model* modelCarryRope_ = nullptr;
	Model* modelHopRope_ = nullptr;

	MapChip* mapchip_ = nullptr;

	Electricity* electricityGimmick_;
	Electricity2* electricityGimmick2_;

	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	Vector3 playerPosition[2]{
	    {-2.0f, 3.0f, 0.0f},
        {2.0f, 3.0f, 0.0f}
    };

	Rope* rope_ = nullptr;

};