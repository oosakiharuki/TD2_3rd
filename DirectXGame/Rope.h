#pragma once
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"

class Player;

class Rope {
public:
	// 初期化
	void Initialize(Player* p1, Player* p2, KamataEngine::Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera* camera);

private:
	KamataEngine::WorldTransform worldTransform;
	KamataEngine::Model* model_ = nullptr;

	Player* player1_ = nullptr;
	Player* player2_ = nullptr;



	float maxLength_;

};