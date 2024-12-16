#include "Player.h"
#include <cassert>

void Player::Initialize(KamataEngine::Vector3 startPosition, KamataEngine::Model* model, int playerId) { 
	input_ = KamataEngine::Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = startPosition;

	playerId_ = playerId;

	assert(model);
	model_ = model;
}

void Player::Update() {
	if (!input_->GetJoystickState(0, state)) {
		return; // コントローラが接続されていない場合
	}

	// 左スティックの入力
	float lx = static_cast<float>(state.Gamepad.sThumbLX) / 32768.0f; // -1.0f～1.0f
	float ly = static_cast<float>(state.Gamepad.sThumbLY) / 32768.0f; // -1.0f～1.0f

	// 右スティックの入力
	float rx = static_cast<float>(state.Gamepad.sThumbRX) / 32768.0f; // -1.0f～1.0f
	float ry = static_cast<float>(state.Gamepad.sThumbRY) / 32768.0f; // -1.0f～1.0f

	// デッドゾーン処理
	const float deadZone = 0.2f; // スティックの感度調整
	if (abs(lx) < deadZone)
		lx = 0.0f;
	if (abs(ly) < deadZone)
		ly = 0.0f;
	if (abs(rx) < deadZone)
		rx = 0.0f;
	if (abs(ry) < deadZone)
		ry = 0.0f;

	// 移動速度
	const float speed = 0.2f;

	// プレイヤーの移動
	if (playerId_ == 1) {
		// 左スティックで移動
		worldTransform_.translation_.x += lx * speed;
		worldTransform_.translation_.y += ly * speed;
	} else if (playerId_ == 2) {
		// 右スティックで移動
		worldTransform_.translation_.x += rx * speed;
		worldTransform_.translation_.y += ry * speed;
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(KamataEngine::Camera* camera) {
	model_->Draw(worldTransform_, *camera); 

	
}

KamataEngine::Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド座標の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Player::SetWorldPosition(const KamataEngine::Vector3& position) { 
	worldTransform_.translation_ = position; 
}
