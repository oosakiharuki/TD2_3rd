#pragma once
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include <cmath>
#include <vector>

class Player;

class Rope {
public:
	~Rope(); // デストラクタを追加
	// 初期化
	void Initialize(Player* p1, Player* p2, KamataEngine::Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera* camera);

private:
	float Length(const KamataEngine::Vector3& v);

private:
	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	KamataEngine::Vector3 controlPoint1_;
	KamataEngine::Vector3 controlPoint2_;
	float slack_ = 1.0f;
	float maxLength_ = 15.0f;
	int segmentCount_ = 5; // ロープの分割数

	KamataEngine::Model* model_ = nullptr;                    // ロープの1セグメント用モデル
	std::vector<KamataEngine::WorldTransform*> ropeSegments_; // 各セグメントのワールド情報（ポインタ）
};
