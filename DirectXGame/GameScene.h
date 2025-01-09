#pragma once
#include <KamataEngine.h>
#include "MapChip.h"
#include "AABB.h"
#include "Box.h"
#include "BrokenBox.h"
#include"Electricity.h"

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
	//ギミック用
	Model* modelElectricity1_ = nullptr;
	Model* modelElectricity2_ = nullptr;
	Model* modelWall1_ = nullptr;
	Model* modelWall2_ = nullptr;

	WorldTransform worldTransform_;
	Camera viewProjection_;
	// uint32_t texture = 0;

	MapChip* mapchip_ = nullptr;
	Box* box_ = nullptr;
	Electricity* electricityGimmick_;
};