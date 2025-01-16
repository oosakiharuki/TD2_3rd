#include "Electricity2.h"

void Electricity2::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* viewProjection) {
	model_ = model; // プレイヤーが触る板用
	model2_ = model2;
	

	worldTransform_.Initialize(); // プレイヤーが触る板用
	worldTransform2_.Initialize();
	

	viewProjection_ = viewProjection;
	objColor.Initialize();
}

void Electricity2::Update() {
	if (Flag) {
		worldTransform2_.translation_.x += 1.0f;
		worldTransform2_.scale_.x -= 1.0f;
	}
	worldTransform_.UpdateMatrix();
	worldTransform2_.UpdateMatrix();
}

void Electricity2::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
	model2_->Draw(worldTransform2_, *viewProjection_, &objColor);
}

void Electricity2::OnCollision() { Flag = true; }

AABB Electricity2::GetAABB() {
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}
