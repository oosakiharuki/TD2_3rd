#include "OnBoxSwitch.h"
#include <cassert>

void OnBoxSwitch::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;

}

void OnBoxSwitch::Update() { 
	
	worldTransform_.UpdateMatrix();

}

void OnBoxSwitch::Draw() {
	model_->Draw(worldTransform_,*viewProjection_);
}

AABB OnBoxSwitch::GetAABB() {
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth, worldPos.y - kHeight, 0.0f};
	aabb.max = {worldPos.x + kWidth, worldPos.y + kHeight, 0.0f};

	return aabb;
}

void OnBoxSwitch::OnCollision() { onFlag = true; }

void OnBoxSwitch::NoBox() { onFlag = false; }
