#include "Artillery.h"
#include"Bullet.h"

void Artillery::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* camera) { 
	model_ = model;
	model2_ = model2;
	viewProjection_ = camera;
	worldTransform_.Initialize();
	worldTransform2_.Initialize();
	objColor.Initialize();
	Timer_ =0;
	
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
	
	//ある一定まで行ったらフラグを戻してタイマーも戻す
	for (Bullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Artillery::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
	for (Bullet* bullet_ : bullets_) {
		bullet_->Draw(*viewProjection_);
	}
}

void Artillery::Fire() {
	// 新しい弾丸を作成
	KamataEngine::Vector3 kSpeed = {1.0f, 0.0f, 0.0f};
	Bullet* newBullet=new Bullet();
	newBullet->Initialize(model2_,worldTransform_.translation_,kSpeed);
	
// 弾を登録する
	bullets_.push_back(newBullet);
}
