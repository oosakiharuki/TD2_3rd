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

void Rope::Initialize(Player* p1, Player* p2, KamataEngine::Input* input, KamataEngine::Model* modelCarry, KamataEngine::Model* modelHop) {
	assert(p1);
	player1_ = p1;
	assert(p2);
	player2_ = p2;
	assert(input);
	input_ = input;

	assert(modelCarry);
	modelCarry_ = modelCarry;
	assert(modelHop);
	modelHop_ = modelHop;

	// ropeSegments_ の初期化
	for (int i = 0; i <= segmentCount_; ++i) {
		auto* segment = new KamataEngine::WorldTransform();
		segment->Initialize();
		ropeSegments_.push_back(segment);
		
		if (i == segmentCount_ / 2) {
			ropeMiddle_ = ropeSegments_[i];
		}
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

	input_->GetJoystickState(0, state);
	input_->GetJoystickStatePrevious(0, preState);

	if (input_->TriggerKey(DIK_SPACE) || 
		(state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
		for (Box* box : boxes_) {
			if (box->GetNowMode() == Box::Mode::Normal) {
				box->SetMode(Box::Mode::Hop);
			} else if (box->GetNowMode() == Box::Mode::Hop) {
				box->SetMode(Box::Mode::Normal);
			}
		}
	}

    // 連続衝突判定 
    int iterations = 10; 
	// 1フレームでの衝突判定回数 
	for (int j = 0; j < iterations; ++j) { 
        for (Box* box : boxes_) {
			bool collisionDetected = CheckCollisionWithBox(box);
			if (collisionDetected) {
				for (int i = 0; i <= segmentCount_; ++i) {
					float t = i / static_cast<float>(segmentCount_);
					KamataEngine::Vector3 position = player1_->GetWorldPosition() * (1.0f - t) + player2_->GetWorldPosition() * t;
					ropeSegments_[i]->translation_ = position;
					ropeSegments_[i]->UpdateMatrix();
				}
			}
		}
	}
} 


void Rope::Draw(KamataEngine::Camera* camera) {
	for (const auto& segment : ropeSegments_) {
		for (const auto& box : boxes_) {
			if (box->GetNowMode() == Box::Mode::Normal) {
				modelCarry_->Draw(*segment, *camera);
			} else if (box->GetNowMode() == Box::Mode::Hop) {
				modelHop_->Draw(*segment, *camera);
			}
		}
	}
}

float Rope::Length(const KamataEngine::Vector3& v) { return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }

KamataEngine::Vector3 Rope::Normalize(const KamataEngine::Vector3& v) { 
	float length = Length(v);
	return KamataEngine::Vector3(v.x / length, v.y / length, v.z / length);
}

bool Rope::CheckCollisionWithBox(Box* box) {
	if (box == nullptr) {
		return false; // boxがnullなら衝突なし
	}

	KamataEngine::Vector3 boxCenter = box->GetCenter();
	float boxRadius = box->GetRadius();

	// ロープの各線分をチェック
	for (size_t i = 0; i < ropeSegments_.size() - 1; ++i) {
		KamataEngine::Vector3 p1 = ropeSegments_[i]->translation_;
		KamataEngine::Vector3 p2 = ropeSegments_[i + 1]->translation_;

		// 最近点を求める
		KamataEngine::Vector3 closestPoint = ClosestPointOnSegment(boxCenter, p1, p2);
		float distance = Length(closestPoint - boxCenter);

		// 衝突が発生している場合
		if (distance <= boxRadius) {
			if (box->GetNowMode() == Box::Mode::Normal) {
    			KamataEngine::Vector3 collisionNormal = Normalize(boxCenter - closestPoint);
    			KamataEngine::Vector3 correction = collisionNormal * (boxRadius - distance) * 1.5f;

    			// ボックスの位置を補正
    			box->SetWorldPosition(boxCenter + correction);

    			// 衝突したセグメント全体に影響を与える
    			KamataEngine::Vector3 segmentDisplacement = correction * 0.5f;
    			ropeSegments_[i]->translation_ -= segmentDisplacement;
    			ropeSegments_[i + 1]->translation_ -= segmentDisplacement;
			} else if (box->GetNowMode() == Box::Mode::Hop) {
				KamataEngine::Vector3 collisionNormal = Normalize(boxCenter - closestPoint);
				KamataEngine::Vector3 correction =collisionNormal * (boxRadius - distance) *1.5f;  
				// ボックスの位置を補正
				box->SetWorldPosition(boxCenter + correction); 
				// ボックスに速度ベクトルを設定 
				box->ApplyForce(collisionNormal); 
				// 速度を適用 
				// // 衝突したセグメント全体に影響を与える 
				KamataEngine::Vector3 segmentDisplacement = correction * 0.5f; ropeSegments_[i]->translation_ -=segmentDisplacement; 
				ropeSegments_[i + 1]->translation_ -= segmentDisplacement;
			}


			// 衝突を検出したのでtrueを返す
			return true;
		}
	}

	return false; // 衝突なし
}

void Rope::OnCollisionBullet() {}


KamataEngine::Vector3 Rope::ClosestPointOnSegment(const KamataEngine::Vector3& point, const KamataEngine::Vector3& p1, const KamataEngine::Vector3& p2) {
	KamataEngine::Vector3 segment = p2 - p1;
	float segmentLengthSquared = Dot(segment, segment);

	if (segmentLengthSquared < 1e-6f) {
		// セグメントがほぼ点のような場合
		return p1;
	}

	float t = Dot(point - p1, segment) / segmentLengthSquared;
	t = std::clamp(t, 0.0f, 1.0f);
	return p1 + t * segment;
}
