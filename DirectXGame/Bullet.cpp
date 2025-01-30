#include "Bullet.h"
#include "makeMath.h"

void Bullet::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity) {
	model_ = model;
	// テクスチャ読み込み
	texture_ = KamataEngine::TextureManager::Load("sample.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void Bullet::Update() {
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	// 座標を移動させる
	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdateMatrix();
}

void Bullet::Draw(const KamataEngine::Camera& camera) { model_->Draw(worldTransform_, camera, texture_); }

void Bullet::OnCollision() { isDead_ = true; }

void Bullet::OnCollision2() { worldTransform_.translation_.x -= 1.0f; }
