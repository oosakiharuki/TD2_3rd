#pragma once
#include <KamataEngine.h>
#include "MapChip.h"

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
	// uint32_t texture = 0;

	MapChip* mapchip_ = nullptr;
};