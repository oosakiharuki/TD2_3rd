#include "MapWall.h"
#include "Player.h"
#include"makeMath.h"
#include <cassert>

using namespace KamataEngine;

void MapWall::Initialize(Model* model, uint32_t texture, Camera* viewProjection, Vector3 position) {

	assert(model);
	model_ = model;
	textureHandle = texture;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	sizeX = worldTransform_.scale_.x;
	sizeY = worldTransform_.scale_.y; 

	viewProjection_ = viewProjection;

}

void MapWall::Update() { worldTransform_.UpdateMatrix(); }

void MapWall::Draw() { model_->Draw(worldTransform_, *viewProjection_,textureHandle); }

void MapWall::OnCollision(Player* player, AABB aabb) {
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	AABB playerAABB = player->GetAABB();

	// 壁のAABBを計算
	AABB wallAABB = aabb;

	KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};
	
	// 水平位置の調整

		if (playerPos.x > rect.leftTop.x && playerPos.y < rect.leftTop.y && 
			playerPos.x > rect.leftBottom.x && playerPos.y > rect.leftBottom.y) {			
			// プレイヤーがドアの右側にいる場合
			correction.x = wallAABB.max.x - playerAABB.min.x;

		}
	    if (playerPos.x < rect.rightTop.x && playerPos.y < rect.rightTop.y && 
			playerPos.x < rect.rightBottom.x && playerPos.y > rect.rightBottom.y) {			
			// プレイヤーがドアの左側にいる場合
			correction.x = wallAABB.min.x - playerAABB.max.x;
		}
	

	// 上下の判定

		if (playerPos.x > rect.leftTop.x && playerPos.y < rect.leftTop.y && 
			playerPos.x < rect.rightTop.x && playerPos.y < rect.rightTop.y) {		
			// プレイヤーがドアの下にいる場合
			correction.y = wallAABB.min.y - playerAABB.max.y;	
		}
		if (playerPos.x > rect.leftBottom.x && playerPos.y > rect.leftBottom.y &&
			playerPos.x < rect.rightBottom.x && playerPos.y > rect.rightBottom.y) {	
			// プレイヤーがドアの上にいる場合
			correction.y = wallAABB.max.y - playerAABB.min.y;
		}


	// プレイヤー位置を修正
	player->SetWorldPosition(playerPos + correction);
	//player->SetHit(hit);
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

	left = worldPos.x - kWidth / 2;
	right = worldPos.x + kWidth / 2;
	top = worldPos.y + kHeight / 2;
	bottom = worldPos.y - kHeight / 2;

	return aabb;
}