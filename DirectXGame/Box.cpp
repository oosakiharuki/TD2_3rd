#include "Box.h"
#include"math/Vector3.h"

void Box::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection) {

	viewProjection_ = viewProjection;
	model_ = model;
	objColor.Initialize();
	worldTransform_.Initialize();
}

void Box::Update() {
	if (Flag) {
		if (20.0f > worldTransform_.translation_.y) {

			worldTransform_.translation_.y += kSpeed;
		}
	}
}

void Box::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
}
