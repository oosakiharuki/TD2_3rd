#include "Door1.h"
#include"Player.h"
#include "Box.h"
#include"makeMath.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Door1::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position, KamataEngine::Vector3 speed) {
	model_ = model;
	kSpeed=speed;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {5.0f,1.0f,1.0f};
	sizeX = worldTransform_.scale_.x;
	sizeY = worldTransform_.scale_.y;

	objColor.Initialize();
	Flag = false;
	
}

void Door1::Update() {
	if (Flag) {
		worldTransform_.translation_ -= kSpeed;
		worldTransform_.scale_.x -= 1.0f;
	}
	if (worldTransform_.scale_.x <= 0) {
		worldTransform_.scale_.x = 0;
		kSpeed = {0};
	}

	worldTransform_.UpdateMatrix();
}

void Door1::Draw() { model_->Draw(worldTransform_, *viewProjection_, &objColor); }

void Door1::OnCollision(Player* player) {
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	AABB playerAABB = player->GetAABB();

	float doorWidth = kWidth * sizeX;
	float doorHeight = kHeight * sizeY;

	// ドアのAABBを計算
	AABB doorAABB;
	doorAABB.min = worldTransform_.translation_ - KamataEngine::Vector3(doorWidth, doorHeight, kHeight / 2);
	doorAABB.max = worldTransform_.translation_ + KamataEngine::Vector3(doorWidth, doorHeight, kHeight / 2);
	// 衝突判定
	if (AABB::IsCollision(playerAABB, doorAABB)) {
		KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};
		// 上下の判定
		if (playerPos.y < worldTransform_.translation_.y - doorHeight) {
			// プレイヤーがドアの下にいる場合
			correction.y = doorAABB.min.y - playerAABB.max.y;
		} else if (playerPos.y > worldTransform_.translation_.y + doorHeight) {
			// プレイヤーがドアの上にいる場合
			correction.y = doorAABB.max.y - playerAABB.min.y;
		} else {
			// 水平位置の調整
			if (playerPos.x < worldTransform_.translation_.x) {
				// プレイヤーがドアの左側にいる場合
				correction.x = doorAABB.min.x - playerAABB.max.x;
			} else if (playerPos.x > worldTransform_.translation_.x + doorWidth) {
				// プレイヤーがドアの右側にいる場合
				correction.x = doorAABB.max.x - playerAABB.min.x;
			}
		}
		// プレイヤー位置を修正
		player->SetWorldPosition(playerPos + correction);
	}
}

void Door1::OnCollisionBox(Box* box) {
	KamataEngine::Vector3 boxPos = box->GetWorldPosition();
	AABB boxAABB = box->GetAABB();

	KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};
	KamataEngine::Vector3 Bound = {0.0f, 0.0f, 0.0f};


	float doorWidth = kWidth * sizeX;
	float doorHeight = kHeight * sizeY;

	// ドアのAABBを計算
	AABB doorAABB;
	doorAABB.min = worldTransform_.translation_ - KamataEngine::Vector3(doorWidth, doorHeight, kHeight / 2);
	doorAABB.max = worldTransform_.translation_ + KamataEngine::Vector3(doorWidth, doorHeight, kHeight / 2);
	// 衝突判定
	if (AABB::IsCollision(boxAABB, doorAABB)) {
		//KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};
		// 上下の判定
		if (boxPos.y < worldTransform_.translation_.y - doorHeight) {
			// プレイヤーがドアの下にいる場合
			correction.y = doorAABB.min.y - boxAABB.max.y;
			Bound.y = -0.1f;
		} else if (boxPos.y > worldTransform_.translation_.y + doorHeight) {
			// プレイヤーがドアの上にいる場合
			correction.y = doorAABB.max.y - boxAABB.min.y;
			Bound.y = 0.1f;
		} else {
			// 水平位置の調整
			if (boxPos.x < worldTransform_.translation_.x) {
				// プレイヤーがドアの左側にいる場合
				correction.x = doorAABB.min.x - boxAABB.max.x;	
				Bound.x = 0.1f;
			} else if (boxPos.x > worldTransform_.translation_.x + doorWidth) {
				// プレイヤーがドアの右側にいる場合
				correction.x = doorAABB.max.x - boxAABB.min.x;
				Bound.x = -0.1f;
			}
		}
		// プレイヤー位置を修正
		box->SetWorldPosition(boxPos + correction);
	}

	correctionPos = correction;

	// ハコ位置を修正
	box->SetWorldPosition(boxPos + correction);
	if (box->GetNowMode() == Box::Mode::Hop) {
		box->ApplyForce(Bound);
	}
}

void Door1::SetCorrectionPos(Player* player) {
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	player->SetWorldPosition(playerPos + correctionPos);
}

void Door1::SetFlag(bool Flag1, bool Flag2) {
	if (Flag1 && Flag2) {
		Flag = true;
		sizeX = -1;
		sizeY = -1;
	}
}

void Door1::Vartical() { 	
	float rotate = float(M_PI) / 2.0f;
	worldTransform_.rotation_ = {0, 0, rotate};
	sizeX = worldTransform_.scale_.y;
	sizeY = worldTransform_.scale_.x;
}
