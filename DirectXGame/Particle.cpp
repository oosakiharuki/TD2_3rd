#include "Particle.h"
#include <cassert>
#include "math/MathUtility.h"

using namespace KamataEngine::MathUtility;

void Particle::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) { 
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// ランダムな速度を設定
	velocity_.x = (rand() % 100 - 50) / 50.0f; // -1.0f ~ 1.0f
	velocity_.y = (rand() % 100 - 50) / 50.0f;
}

void Particle::Update() {
	if (!isActive_)return;

	// 移動
	worldTransform_.translation_ += velocity_;

	// 徐々に減速する
	velocity_ *= 0.85f;

	// 寿命の管理
	timer_ += 1.0f / 60.0f;
	if (timer_ >= lifetime_) {
		isActive_ = false;
	}

	worldTransform_.UpdateMatrix();
}

void Particle::Draw() {
	if (isActive_ && model_) {
		model_->Draw(worldTransform_, *camera_);
	}
}
