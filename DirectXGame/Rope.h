#pragma once
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include <cmath>
#include <vector>
#include "input/Input.h"
#include <list>

class Player;
class Box;

class Rope {
public:
	~Rope(); // デストラクタを追加
	// 初期化
	void Initialize(Player* p1, Player* p2, KamataEngine::Input* input, KamataEngine::Model* modelCarry, KamataEngine::Model* modelHop);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera* camera);

	bool CheckCollisionWithBox(Box* box);

	void SetBoxes(const std::list<Box*>& boxes) { boxes_ = boxes; }
	const KamataEngine::WorldTransform& GetWorldTransform() { return *ropeMiddle_; }

private:
	float Length(const KamataEngine::Vector3& v);
	KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v);
	KamataEngine::Vector3 ClosestPointOnSegment(const KamataEngine::Vector3& point, const KamataEngine::Vector3& p1, const KamataEngine::Vector3& p2);

private:
	Player* player1_ = nullptr;
	Player* player2_ = nullptr;
	Box* box_ = nullptr;
	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Vector3 controlPoint1_;
	KamataEngine::Vector3 controlPoint2_;
	float slack_ = 1.0f;
	float maxLength_ = 6.0f;
	int segmentCount_ = 11; // ロープの分割数

	KamataEngine::Model* modelCarry_ = nullptr;
	KamataEngine::Model* modelHop_ = nullptr;

	std::vector<KamataEngine::WorldTransform*> ropeSegments_; // 各セグメントのワールド情報（ポインタ）
	KamataEngine::WorldTransform* ropeMiddle_; //ロープの真ん中をカメラ位置にする

	std::list<Box*> boxes_;

	XINPUT_STATE state, preState;
};
