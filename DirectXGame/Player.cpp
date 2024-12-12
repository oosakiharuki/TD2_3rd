#include "Player.h"
#include <cassert>

void Player::Initialize(KamataEngine::Vector3 startPosition, KamataEngine::Model* model, int playerId) { 
	worldTransform_.Initialize();
	worldTransform_.translation_ = startPosition;

	playerId_ = playerId;

	assert(model);
	model_ = model;

}

void Player::Update() {
	// プレイヤーの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};
	// 最大速度
	const float kMaxSpeed = 0.5f;

	// プレイヤー1か2か
	if (playerId_ == 1) {
		// ジョイスティックによる移動
		if (input_->GetJoystickState(0, state)) {
			// デッドゾーンを設定（32768の範囲内）
			const int32_t kDeadZoneL = 8000; // 左スティックのデッドゾーン
			input_->SetJoystickDeadZone(0, kDeadZoneL, 0);

			// 左スティックの値を取得
			float lx = static_cast<float>(state.Gamepad.sThumbLX) / 32768.0f; // -1.0 ～ 1.0 に正規化
			float ly = static_cast<float>(state.Gamepad.sThumbLY) / 32768.0f; // -1.0 ～ 1.0 に正規化

			// デッドゾーンの適用
			if (fabs(lx) > (kDeadZoneL / 32768.0f)) {
				move.x += lx * moveSpeed_;
			}
			if (fabs(ly) > (kDeadZoneL / 32768.0f)) {
				move.y += ly * moveSpeed_;
			}
		}
	} else if (playerId_ == 2) {
		// ジョイスティックによる移動
		if (input_->GetJoystickState(0, state)) {
			// デッドゾーンを設定（32768の範囲内）
			const int32_t kDeadZoneR = 8000; // →スティックのデッドゾーン
			input_->SetJoystickDeadZone(0, kDeadZoneR, 0);

			// 左スティックの値を取得
			float rx = static_cast<float>(state.Gamepad.sThumbRX) / 32768.0f; // -1.0 ～ 1.0 に正規化
			float ry = static_cast<float>(state.Gamepad.sThumbRY) / 32768.0f; // -1.0 ～ 1.0 に正規化

			// デッドゾーンの適用
			if (fabs(rx) > (kDeadZoneR / 32768.0f)) {
				move.x += rx * moveSpeed_;
			}
			if (fabs(ry) > (kDeadZoneR / 32768.0f)) {
				move.y += ry * moveSpeed_;
			}
		}
	}

	playerVelocity.x += move.x;
	playerVelocity.y += move.y;
	playerVelocity.z += move.z;

		// 速度計算
	float speed = sqrt(playerVelocity.x * playerVelocity.x + playerVelocity.y * playerVelocity.y);

	// 上限を設定
	if (speed > kMaxSpeed) {
		float scale = kMaxSpeed / speed;
		playerVelocity.x *= scale;
		playerVelocity.y *= scale;
	}

	worldTransform_.translation_.x += playerVelocity.x;
	worldTransform_.translation_.y += playerVelocity.y;
	worldTransform_.translation_.z += playerVelocity.z;
}

void Player::Draw(KamataEngine::Camera* camera) {
	model_->Draw(worldTransform_, *camera); 
}
