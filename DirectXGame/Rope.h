#pragma once
#include "3d/Camera.h"

class Player;

class Rope {
public:
	// 初期化
	void Initialize(Player* p1, Player* p2);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera* camera);

private:
	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	float maxLength_;

};