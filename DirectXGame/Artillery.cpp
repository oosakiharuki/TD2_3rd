#include "Artillery.h"
#include "Bullet.h"

void Artillery::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* camera) {
	model_ = model;
	model2_ = model2;
	viewProjection_ = camera;
	worldTransform_.Initialize();
	worldTransform2_.Initialize();
	objColor.Initialize();
	Timer_ = 0;
}

void Artillery::Update() {
	

		bullets_.remove_if([](Bullet* bullet_) {
			if (bullet_->IsDead()) {
				delete bullet_;
				return true;
			}
			return false;
		});

		Timer_--;
		if (Timer_ < 0) {
			Fire();
			Timer_ = kFireInterval;
		}

		// ある一定まで行ったらフラグを戻してタイマーも戻す
		for (Bullet* bullet : bullets_) {
			bullet->Update();
		}
	    worldTransform_.translation_={2.0f, 2.0f, 0.0f};
	    worldTransform_.UpdateMatrix();
}

void Artillery::Draw() {
	

		model_->Draw(worldTransform_, *viewProjection_, &objColor);
	
	for (Bullet* bullet_ : bullets_) {
		bullet_->Draw(*viewProjection_);
	}
}

void Artillery::Fire() {
	// 新しい弾丸を作成
	KamataEngine::Vector3 kSpeed = {0.5f, 0.0f, 0.0f};
	Bullet* newBullet = new Bullet();
	worldTransform2_.translation_.x = worldTransform_.translation_.x + 2.0f;
	worldTransform2_.translation_.y = worldTransform_.translation_.y;
	worldTransform2_.translation_.z = worldTransform_.translation_.z;
	newBullet->Initialize(model2_, worldTransform2_.translation_ , kSpeed);

	// 弾を登録する
	bullets_.push_back(newBullet);
}

void Artillery::OnCollision() { isDead = true; }
