#include "BrokenBox.h"

void BrokenBox::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection) {
	model_=model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	objColor.Initialize();
}

void BrokenBox::Update() {}

void BrokenBox::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
}
