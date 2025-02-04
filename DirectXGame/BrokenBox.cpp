#include "BrokenBox.h"
#include "Player.h"
#include"makeMath.h"
#include <cassert>
#include "Box.h"

BrokenBox::~BrokenBox() {
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}

void BrokenBox::Initialize(KamataEngine::Model* model, KamataEngine::Model* modelParticlel, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position) {
	assert(model);
	model_ = model;
	assert(modelParticlel);
	modelParticle_ = modelParticlel;;

	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	objColor.Initialize();

}

void BrokenBox::Update() { 
	worldTransform_.UpdateMatrix();

	// パーティクルの更新
	for (Particle* particle : particles_) {
		particle->Update();
	}

	// 破壊後の処理
	if (isBreak) {
		// パーティクルを一定数まで生成
		if (particleCount_ < particleLimit_) {
			for (int i = 0; i < 5; i++) {
				if (particleCount_ >= particleLimit_)
					break;

				Particle* particle = new Particle();
				particle->Initialize(modelParticle_, viewProjection_, worldTransform_.translation_);
				particles_.push_back(particle);
				particleCount_++;
			}
		}

		// 無効なパーティクルを削除
		particles_.remove_if([](Particle* particle) {
			if (!particle->IsActive()) {
				delete particle;
				return true;
			}
			return false;
		});
	}
}

void BrokenBox::Draw() { 
	if (!isBreak) {
    	model_->Draw(worldTransform_, *viewProjection_, &objColor); 
	}

	// パーティクルの描画
	for (Particle* particle : particles_) {
		particle->Draw();
	}
}


KamataEngine::Vector3 BrokenBox::GetWorldPosition() { 
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド座標の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void BrokenBox::OnCollision() {
	isBreak = true;
}

AABB BrokenBox::GetAABB() {
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth, worldPos.y - kHeight, 0.0f};
	aabb.max = {worldPos.x + kWidth, worldPos.y + kHeight, 0.0f};

	rect.leftTop = {aabb.min.x, aabb.max.y};
	rect.rightTop = {aabb.max.x, aabb.max.y};
	rect.leftBottom = {aabb.min.x, aabb.min.y};
	rect.rightBottom = {aabb.max.x, aabb.min.y};

	return aabb;
}

void BrokenBox::OnCollisionPlayer(Player* player, AABB aabb) {
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	AABB playerAABB = player->GetAABB();

	// 壁のAABBを計算
	AABB wallAABB = aabb;

	KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};

	// 水平位置の調整

	if (playerPos.x > rect.leftTop.x && playerPos.y < rect.leftTop.y && playerPos.x > rect.leftBottom.x && playerPos.y > rect.leftBottom.y) {
		// プレイヤーがドアの右側にいる場合
		correction.x = wallAABB.max.x - playerAABB.min.x;
	}
	if (playerPos.x < rect.rightTop.x && playerPos.y < rect.rightTop.y && playerPos.x < rect.rightBottom.x && playerPos.y > rect.rightBottom.y) {
		// プレイヤーがドアの左側にいる場合
		correction.x = wallAABB.min.x - playerAABB.max.x;
	}

	// 上下の判定

	if (playerPos.x > rect.leftTop.x && playerPos.y < rect.leftTop.y && playerPos.x < rect.rightTop.x && playerPos.y < rect.rightTop.y) {
		// プレイヤーがドアの下にいる場合
		correction.y = wallAABB.min.y - playerAABB.max.y;
	}
	if (playerPos.x > rect.leftBottom.x && playerPos.y > rect.leftBottom.y && playerPos.x < rect.rightBottom.x && playerPos.y > rect.rightBottom.y) {
		// プレイヤーがドアの上にいる場合
		correction.y = wallAABB.max.y - playerAABB.min.y;
	}

	// プレイヤー位置を修正
	player->SetWorldPosition(playerPos + correction);
}


void BrokenBox::OnCollisionBox(Box* box, AABB aabb) {
	KamataEngine::Vector3 boxPos = box->GetWorldPosition();
	AABB boxAABB = box->GetAABB();

	// 壁のAABBを計算
	AABB wallAABB = aabb;

	KamataEngine::Vector3 correction = {0.0f, 0.0f, 0.0f};

	// 水平位置の調整

	if (boxPos.x > rect.leftTop.x && boxPos.y < rect.leftTop.y && boxPos.x > rect.leftBottom.x && boxPos.y > rect.leftBottom.y) {
		// ハコが壁の右側にいる場合
		correction.x = wallAABB.max.x - boxAABB.min.x;
	}
	if (boxPos.x < rect.rightTop.x && boxPos.y < rect.rightTop.y && boxPos.x < rect.rightBottom.x && boxPos.y > rect.rightBottom.y) {
		// ハコが壁の左側にいる場合
		correction.x = wallAABB.min.x - boxAABB.max.x;
	}

	// 上下の判定

	if (boxPos.x > rect.leftTop.x && boxPos.y < rect.leftTop.y && boxPos.x < rect.rightTop.x && boxPos.y < rect.rightTop.y) {
		// ハコが壁の下にいる場合
		correction.y = wallAABB.min.y - boxAABB.max.y;
	}
	if (boxPos.x > rect.leftBottom.x && boxPos.y > rect.leftBottom.y && boxPos.x < rect.rightBottom.x && boxPos.y > rect.rightBottom.y) {
		// ハコが壁の上にいる場合
		correction.y = wallAABB.max.y - boxAABB.min.y;
	}

	correctionPos = correction;

	// ハコ位置を修正
	box->SetWorldPosition(boxPos + correction);
}

void BrokenBox::SetCorrectionPos(Player* player) {
	KamataEngine::Vector3 playerPos = player->GetWorldPosition();
	player->SetWorldPosition(playerPos + correctionPos);
}