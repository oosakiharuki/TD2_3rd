#define NOMINMAX
#include "Rope.h"
#include "math/MathUtility.h"
#include "Player.h"
#include <algorithm>
#include <cassert>
#include "Box.h"

using namespace KamataEngine::MathUtility;

Rope::~Rope() {
	for (auto segment : ropeSegments_) {
		delete segment;
	}
	ropeSegments_.clear();
}

void Rope::Initialize(Player* p1, Player* p2, KamataEngine::Model* model) {
	assert(p1);
	player1_ = p1;
	assert(p2);
	player2_ = p2;
	assert(model);
	model_ = model;

	// ropeSegments_ の初期化
	for (int i = 0; i <= segmentCount_; ++i) {
		auto* segment = new KamataEngine::WorldTransform();
		segment->Initialize();
		ropeSegments_.push_back(segment);
	}
}

void Rope::Update() {
	// プレイヤー間の位置を取得
	KamataEngine::Vector3 pos1 = player1_->GetWorldPosition();
	KamataEngine::Vector3 pos2 = player2_->GetWorldPosition();

	// プレイヤー間の距離を計算
	KamataEngine::Vector3 diff = pos2 - pos1;
	float distance = Length(diff);

	// 距離が最大長を超える場合、補正する
	if (distance > maxLength_) {
		KamataEngine::Vector3 direction = diff / distance; // 単位ベクトル
		float excess = distance - maxLength_;              // 超過距離
		float correctionFactor = 0.1f;                     // 補正を1フレームで行う割合（0.0～1.0）
		KamataEngine::Vector3 correction = direction * (excess * correctionFactor);

		// プレイヤーの位置を補正
		pos1 += correction * 0.5f;
		pos2 -= correction * 0.5f;
		player1_->SetWorldPosition(pos1);
		player2_->SetWorldPosition(pos2);
	}

	// ロープのセグメントを更新（線形補間）
	for (int i = 0; i <= segmentCount_; ++i) {
		float t = i / static_cast<float>(segmentCount_);
		KamataEngine::Vector3 position = pos1 * (1.0f - t) + pos2 * t; // 線形補間
		ropeSegments_[i]->translation_ = position;
		ropeSegments_[i]->UpdateMatrix();
	}

	//CheckCollisionWithBox(*box_);
} 


void Rope::Draw(KamataEngine::Camera* camera) {
	for (const auto& segment : ropeSegments_) {
		model_->Draw(*segment, *camera);
	}
}

float Rope::Length(const KamataEngine::Vector3& v) { return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }

KamataEngine::Vector3 Rope::Normalize(const KamataEngine::Vector3& v) { 
	float length = Length(v);
	return KamataEngine::Vector3(v.x / length, v.y / length, v.z / length);
}

bool Rope::CheckCollisionWithBox(Box& box) { 
	KamataEngine::Vector3 boxCenter = box.GetCenter();
	float boxRadius = box.GetRadius();
	for (size_t i = 0; i < ropeSegments_.size() - 1; ++i) {
		KamataEngine::Vector3 p1 = ropeSegments_[i]->translation_;
		KamataEngine::Vector3 p2 =
		    ropeSegments_[i + 1]->translation_; 
		// ボックスの円がロープの線分と交差しているかをチェック 
		KamataEngine::Vector3 closestPoint = ClosestPointOnSegment(boxCenter, p1, p2); 
		float distance =Length(closestPoint - boxCenter); 
		if (distance <= boxRadius) { 
			KamataEngine::Vector3 collisionNormal = Normalize(boxCenter - closestPoint);
		    KamataEngine::Vector3 force = collisionNormal * (boxRadius - distance); 
			box.ApplyForce(force); 
			return true; // 衝突検出 
		} 
	} 
	return false; // 衝突なし
}


KamataEngine::Vector3 Rope::ClosestPointOnSegment(const KamataEngine::Vector3& point, const KamataEngine::Vector3& p1, const KamataEngine::Vector3& p2) {
	KamataEngine::Vector3 segment = p2 - p1;
	float t = Dot(point - p1, segment) / Dot(segment, segment);
	t = std::clamp(t, 0.0f, 1.0f);
	return p1 + t * segment;
}
