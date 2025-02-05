#include "Box.h"
#include"math/Vector3.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include "math/MathUtility.h"

using namespace KamataEngine::MathUtility;

void Box::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position, KamataEngine::Vector3 startPos) {

	viewProjection_ = viewProjection;
	model_ = model;
	objColor.Initialize();
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	startPos_ = startPos;
}

void Box::Update() {
	if (Flag) {
		if (20.0f > worldTransform_.translation_.y) {

			worldTransform_.translation_.y += kSpeed;
		}
	}


    if (mode_ == Mode::Normal) { 
		// 通常の押す処理 
		worldTransform_.translation_ += velocity_; 
	} else if (mode_ == Mode::Hop) { 
		// 飛ばす処理
		worldTransform_.translation_ += velocity_;
	}

	velocity_ *= 0.98f;
	worldTransform_.UpdateMatrix();
}

void Box::Draw() { model_->Draw(worldTransform_, *viewProjection_, &objColor); }

void Box::ApplyForce(const KamataEngine::Vector3& force) { 
	velocity_ += force * kSpeed; }

KamataEngine::Vector3 Box::GetWorldPosition() { 
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド座標の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}


AABB Box::GetAABB() {
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth, worldPos.y - kHeight, 0.0f};
	aabb.max = {worldPos.x + kWidth, worldPos.y + kHeight, 0.0f};

	return aabb;
}