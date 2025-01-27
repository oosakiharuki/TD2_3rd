#include "Door2.h"
#include"makeMath.h"
#include"Player.h"

void Door2::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 speed) {
	model_ = model;
	kSpeed = speed;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {5.0f, 1.0f, 1.0f};
	objColor.Initialize();
	Flag = false;
	kWidth = worldTransform_.scale_.x;
	kHeight = worldTransform_.scale_.y;
}
void Door2::Update() {
	if (Flag) {
		worldTransform_.translation_ += kSpeed;
		worldTransform_.scale_.x -= 1.0f;
	}
	if (worldTransform_.scale_.x <= 0) {
		worldTransform_.scale_.x = 0;
		kSpeed = {0};
	}
	worldTransform_.UpdateMatrix();
	kWidth = worldTransform_.scale_.x;
	kHeight = worldTransform_.scale_.y;
}
void Door2::Draw() { model_->Draw(worldTransform_, *viewProjection_, &objColor); }
void Door2::OnCollision(Player* player) {
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	AABB playerAABB = player->GetAABB();
	// ドアのAABBを計算
	AABB doorAABB;
	doorAABB.min = worldTransform_.translation_ - KamataEngine::Vector3(kWidth / 2, 0.0f, kHeight / 2);
	doorAABB.max = worldTransform_.translation_ + KamataEngine::Vector3(kWidth / 2, kHeight, kHeight / 2);
	// 衝突判定
	if (AABB::IsCollision(playerAABB, doorAABB)) {
		KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};
		// 上下の判定
		if (playerPos.y < worldTransform_.translation_.y) {
			// プレイヤーがドアの下にいる場合
			correction.y = doorAABB.min.y - playerAABB.max.y;
		} else if (playerPos.y > worldTransform_.translation_.y + kHeight) {
			// プレイヤーがドアの上にいる場合
			correction.y = doorAABB.max.y - playerAABB.min.y;
		} else {
			// 水平位置の調整
			if (playerPos.x < worldTransform_.translation_.x) {
				// プレイヤーがドアの左側にいる場合
				correction.x = doorAABB.min.x - playerAABB.max.x;
			} else {
				// プレイヤーがドアの右側にいる場合
				correction.x = doorAABB.max.x - playerAABB.min.x;
			}
		}
		// プレイヤー位置を修正
		player->SetWorldPosition(playerPos + correction);
	}
}
void Door2::SetFlag(bool Flag1) { Flag = Flag1; }