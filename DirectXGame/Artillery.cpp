#include "Artillery.h"

void Artillery::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* camera) { 
	model_ = model;
	model2_ = model2;
	viewProjection_ = camera;
	worldTransform_.Initialize();
	worldTransform2_.Initialize();
	objColor.Initialize();
	Timer_ = 100;
}

void Artillery::Update() { Timer_--;
	if (Timer_ <= 0) {
		Flag = true;
		worldTransform2_.translation_.x += 1.0f;
		Timer_ = 100;
	}
	if (Flag) {
		worldTransform2_.translation_.x += 1.0f;
		Timer_ = 100;

	}
	//ある一定まで行ったらフラグを戻してタイマーも戻す

}

void Artillery::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
	model2_->Draw(worldTransform2_, *viewProjection_, &objColor);
}
