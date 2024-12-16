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
	KamataEngine::Vector3 diff = pos1 - pos2;
	float distance = Length(diff);

	// 距離が最大長を超える場合、補正する
	if (distance > maxLength_) {
		KamataEngine::Vector3 direction = diff / distance; // 単位ベクトル
		KamataEngine::Vector3 correction = direction * (distance - maxLength_);
		pos1 -= correction * 0.5f;
		pos2 += correction * 0.5f;
		player1_->SetWorldPosition(pos1);
		player2_->SetWorldPosition(pos2);
	}

	// ロープの緩み量を調整
	slack_ = std::max(distance / 5.0f, 1.0f);
	controlPoint1_ = pos1 + KamataEngine::Vector3(0, -slack_, 0);
	controlPoint2_ = pos2 + KamataEngine::Vector3(0, -slack_, 0);

	// ロープのセグメントを更新
	for (int i = 0; i <= segmentCount_; ++i) {
		float t = i / static_cast<float>(segmentCount_);
		KamataEngine::Vector3 position = Bezier(t, pos1, controlPoint1_, controlPoint2_, pos2);
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

KamataEngine::Vector3 Rope::Normalize(const KamataEngine::Vector3& v) {
	float length = Length(v);
	return KamataEngine::Vector3(v.x / length, v.y / length, v.z / length);
}

KamataEngine::Vector3 Rope::Bezier(float t, const KamataEngine::Vector3& p0, const KamataEngine::Vector3& p1, const KamataEngine::Vector3& p2, const KamataEngine::Vector3& p3) {
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;
	float uuu = uu * u;
	float ttt = tt * t;
	KamataEngine::Vector3 p = p0 * uuu;
	p += p1 * (3 * uu * t);
	p += p2 * (3 * u * tt);
	p += p3 * ttt;
	return p;
}


