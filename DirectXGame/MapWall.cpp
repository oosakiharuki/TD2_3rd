#include "MapWall.h"
#include "Player.h"
#include "Box.h"
#include"makeMath.h"
#include <cassert>

using namespace KamataEngine;

void MapWall::Initialize(Model* model, uint32_t texture, Camera* viewProjection, Vector3 position) {

	assert(model);
	model_ = model;
	textureHandle = texture;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	viewProjection_ = viewProjection;
}

void MapWall::Update() { worldTransform_.UpdateMatrix(); }

void MapWall::Draw() { model_->Draw(worldTransform_, *viewProjection_,textureHandle); }

void MapWall::OnCollisionPlayer(Player* player, AABB aabb) {
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	AABB playerAABB = player->GetAABB();

	// 壁のAABBを計算
	AABB wallAABB = aabb;

	KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};

	// 水平位置の調整

	if (playerPos.x > rect.leftTop.x && playerPos.y < rect.leftTop.y && playerPos.x > rect.leftBottom.x && playerPos.y > rect.leftBottom.y) {
		// プレイヤーが壁の右側にいる場合
		correction.x = wallAABB.max.x - playerAABB.min.x;
	}
	if (playerPos.x < rect.rightTop.x && playerPos.y < rect.rightTop.y && playerPos.x < rect.rightBottom.x && playerPos.y > rect.rightBottom.y) {
		// プレイヤーが壁の左側にいる場合
		correction.x = wallAABB.min.x - playerAABB.max.x;
	}

	// 上下の判定

	if (playerPos.x > rect.leftTop.x && playerPos.y < rect.leftTop.y && 
		playerPos.x < rect.rightTop.x && playerPos.y < rect.rightTop.y) {
		// プレイヤーが壁の下にいる場合
		correction.y = wallAABB.min.y - playerAABB.max.y;
	}
	if (playerPos.x > rect.leftBottom.x && playerPos.y > rect.leftBottom.y &&
		playerPos.x < rect.rightBottom.x && playerPos.y > rect.rightBottom.y) {
		// プレイヤーが壁の上にいる場合
		correction.y = wallAABB.max.y - playerAABB.min.y;
	}


	// プレイヤー位置を修正
	player->SetWorldPosition(playerPos + correction);
}


void MapWall::OnCollisionBox(Box* box, AABB aabb) {
	KamataEngine::Vector3 boxPos = box->GetWorldPosition();
	AABB boxAABB = box->GetAABB();

	// 壁のAABBを計算
	AABB wallAABB = aabb;

	KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};
	KamataEngine::Vector3 Bound = {0.0f, 0.0f, 0.0f};

	// 水平位置の調整

	if (boxPos.x > rect.leftTop.x && boxPos.y < rect.leftTop.y && boxPos.x > rect.leftBottom.x && boxPos.y > rect.leftBottom.y) {
		// ハコが壁の右側にいる場合
		correction.x = wallAABB.max.x - boxAABB.min.x;
		Bound.x = 0.1f;
	}
	if (boxPos.x < rect.rightTop.x && boxPos.y < rect.rightTop.y && boxPos.x < rect.rightBottom.x && boxPos.y > rect.rightBottom.y) {
		// ハコが壁の左側にいる場合
		correction.x = wallAABB.min.x - boxAABB.max.x;
		Bound.x = -0.1f;
	}

	// 上下の判定

	if (boxPos.x > rect.leftTop.x && boxPos.y < rect.leftTop.y && boxPos.x < rect.rightTop.x && boxPos.y < rect.rightTop.y) {
		// ハコが壁の下にいる場合
		correction.y = wallAABB.min.y - boxAABB.max.y;
		Bound.y = -0.1f;
	}
	if (boxPos.x > rect.leftBottom.x && boxPos.y > rect.leftBottom.y && boxPos.x < rect.rightBottom.x && boxPos.y > rect.rightBottom.y) {
		// ハコが壁の上にいる場合
		correction.y = wallAABB.max.y - boxAABB.min.y;
		Bound.y = 0.1f;
	}

	correctionPos = correction;

	// ハコ位置を修正
	box->SetWorldPosition(boxPos + correction);
	if (box->GetNowMode() == Box::Mode::Hop) {
		box->ApplyForce(Bound);
	}
}

void MapWall::SetCorrectionPos(Player* player) { 
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	player->SetWorldPosition(playerPos + correctionPos); 
}

AABB MapWall::GetAABB() {
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth , worldPos.y - kHeight , 0.0f};
	aabb.max = {worldPos.x + kWidth , worldPos.y + kHeight, 0.0f};

	rect.leftTop = {aabb.min.x , aabb.max.y };
	rect.rightTop = {aabb.max.x , aabb.max.y };
	rect.leftBottom = {aabb.min.x , aabb.min.y };
	rect.rightBottom = {aabb.max.x , aabb.min.y };

	return aabb;
}