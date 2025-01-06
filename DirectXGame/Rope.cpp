#define NOMINMAX
#include "Rope.h"
#include "MathUtility.h"
#include "Player.h"
#include <algorithm>
#include <cassert>

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
} 


void Rope::Draw(KamataEngine::Camera* camera) {
	for (const auto& segment : ropeSegments_) {
		model_->Draw(*segment, *camera);
	}
}

float Rope::Length(const KamataEngine::Vector3& v) { return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }




