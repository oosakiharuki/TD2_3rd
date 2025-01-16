#include "Player.h"
#include <cassert>
#include"Electricity.h"
#include"Electricity2.h"

void Player::Initialize(KamataEngine::Vector3 startPosition, KamataEngine::Model* model, int playerId) { 
	input_ = KamataEngine::Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = startPosition;

	playerId_ = playerId;

	assert(model);
	model_ = model;
}

void Player::Update() {
	float lx = 0, ly = 0, rx = 0, ry = 0;

	if (input_->GetJoystickState(0, state)) {
		 // 左スティックの入力
    	 lx = static_cast<float>(state.Gamepad.sThumbLX) / 32768.0f; // -1.0f～1.0f
    	 ly = static_cast<float>(state.Gamepad.sThumbLY) / 32768.0f; // -1.0f～1.0f

    	// 右スティックの入力
    	 rx = static_cast<float>(state.Gamepad.sThumbRX) / 32768.0f; // -1.0f～1.0f
    	 ry = static_cast<float>(state.Gamepad.sThumbRY) / 32768.0f; // -1.0f～1.0f

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
	}

	// 移動速度
	const float speed = 0.2f;

	// プレイヤーの移動
	if (playerId_ == 1) {
		// コントローラで移動（左スティック）
		worldTransform_.translation_.x += lx * speed;
		worldTransform_.translation_.y += ly * speed;

		// キーボードによる移動
		if (input_->PushKey(DIK_A)) {
			worldTransform_.translation_.x -= speed;
		}
		if (input_->PushKey(DIK_D)) {
			worldTransform_.translation_.x += speed;
		}
		if (input_->PushKey(DIK_W)) {
			worldTransform_.translation_.y += speed;
		}
		if (input_->PushKey(DIK_S)) {
			worldTransform_.translation_.y -= speed;
		}
	} else if (playerId_ == 2) {
		// コントローラで移動（右スティック）
		worldTransform_.translation_.x += rx * speed;
		worldTransform_.translation_.y += ry * speed;

		// キーボードによる移動
		if (input_->PushKey(DIK_LEFT)) {
			worldTransform_.translation_.x -= speed;
		}
		if (input_->PushKey(DIK_RIGHT)) {
			worldTransform_.translation_.x += speed;
		}
		if (input_->PushKey(DIK_UP)) {
			worldTransform_.translation_.y += speed;
		}
		if (input_->PushKey(DIK_DOWN)) {
			worldTransform_.translation_.y -= speed;
		}
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

AABB Player::GetAABB() {
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Player::OnCollision(const Electricity* electricity) { (void)electricity; }

void Player::OnCollision2(const Electricity2* electricity2) { (void)electricity2; }
