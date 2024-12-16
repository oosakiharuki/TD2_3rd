#pragma once
#include <KamataEngine.h>
#include "Player.h"


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

	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	Vector3 playerPosition[2]{
	    {100.0f, 300.0f, 0.0f},
        {500.0f, 300.0f, 0.0f}
    };
};