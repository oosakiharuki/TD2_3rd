#pragma once
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include <cmath>
#include <vector>

class Player;
class Box;

class Rope {
public:
	~Rope(); // デストラクタを追加
	// 初期化
	void Initialize(Player* p1, Player* p2, KamataEngine::Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera* camera);

	bool CheckCollisionWithBox(Box& box);

	void GetBox(Box* box) {box_=box;}

private:
	float Length(const KamataEngine::Vector3& v);
	KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v);
	KamataEngine::Vector3 ClosestPointOnSegment(const KamataEngine::Vector3& point, const KamataEngine::Vector3& p1, const KamataEngine::Vector3& p2);

private:
	Player* player1_ = nullptr;
	Player* player2_ = nullptr;

	KamataEngine::Vector3 controlPoint1_;
	KamataEngine::Vector3 controlPoint2_;
	float slack_ = 1.0f;
	float maxLength_ = 15.0f;
	int segmentCount_ = 10; // ロープの分割数

	KamataEngine::Model* model_ = nullptr;                    // ロープの1セグメント用モデル
	std::vector<KamataEngine::WorldTransform*> ropeSegments_; // 各セグメントのワールド情報（ポインタ）

	Box* box_ = nullptr;
};
