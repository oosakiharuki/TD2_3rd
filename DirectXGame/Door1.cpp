#include "Door1.h"
#include"Player.h"
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

void Door1::OnCollision(Player* player) { player; }

void Door1::SetFlag(bool Flag1, bool Flag2) {
	if (Flag1 && Flag2) {
		Flag = true;
	}
}

void Door1::Vartical() { 	
	float rotate = float(M_PI) / 2.0f;
	worldTransform_.rotation_ = {0, 0, rotate};
}
