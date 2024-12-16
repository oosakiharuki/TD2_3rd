#include "Player.h"
#include <cassert>

void Player::Initialize(KamataEngine::Vector3 startPosition, KamataEngine::Model* model, int playerId) { 
	input_ = KamataEngine::Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = startPosition;

	playerId_ = playerId;

	assert(model);
	model_ = model;

	const int32_t kDeadZoneL = 8000;
	const int32_t kDeadZoneR = 8000;
	input_->SetJoystickDeadZone(0, kDeadZoneL, kDeadZoneR);
}

void Player::Update() {
	// ジョイスティックの状態
	if (!input_->GetJoystickState(0, state)) {
		return; // 取得に失敗したら更新処理を終了
	}

	KamataEngine::Vector3 move = {0, 0, 0};
	const float kMaxSpeed = 0.5f;

	// 左スティックの処理 (プレイヤー1)
	if (playerId_ == 1) {
		float lx = static_cast<float>(state.Gamepad.sThumbLX) / 32768.0f;
		float ly = static_cast<float>(state.Gamepad.sThumbLY) / 32768.0f;

		if (fabs(lx) > 8000.0f / 32768.0f)
			move.x += lx * moveSpeed_;
		if (fabs(ly) > 8000.0f / 32768.0f)
			move.y += ly * moveSpeed_;
	}
	// 右スティックの処理 (プレイヤー2)
	else if (playerId_ == 2) {
		float rx = static_cast<float>(state.Gamepad.sThumbRX) / 32768.0f;
		float ry = static_cast<float>(state.Gamepad.sThumbRY) / 32768.0f;

		if (fabs(rx) > 8000.0f / 32768.0f)
			move.x += rx * moveSpeed_;
		if (fabs(ry) > 8000.0f / 32768.0f)
			move.y += ry * moveSpeed_;
	}

	// 速度計算
	float speed = sqrt(move.x * move.x + move.y * move.y);
	if (speed > kMaxSpeed) {
		float scale = kMaxSpeed / speed;
		move.x *= scale;
		move.y *= scale;
	}

	// プレイヤーの位置更新
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

}

void Player::Draw(KamataEngine::Camera* camera) {
	model_->Draw(worldTransform_, *camera); 
}
