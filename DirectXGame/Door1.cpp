#include "Door1.h"
#include"Player.h"
#include"makeMath.h"

void Door1::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 speed) {
	model_ = model;
	kSpeed=speed;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {5.0f,1.0f,1.0f};
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

}

void Door1::SetFlag(bool Flag1) {
	 Flag = Flag1;
}
