#include "Electricity.h"

void Electricity::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Model* model3, KamataEngine::Model* model4, KamataEngine::Camera* viewProjection) {
	model_ = model;//プレイヤーが触る板用
	model2_ = model2;
	model3_ = model3;//動くところ用
	model4_ = model4;

	worldTransform_.Initialize();//プレイヤーが触る板用
	worldTransform2_.Initialize();
	worldTransform3_.Initialize();//動くところ用
	worldTransform4_.Initialize();

	viewProjection_ = viewProjection;
	objColor.Initialize();

}

void Electricity::Update() {
	if (Flag) {
		worldTransform3_.translation_.x -= 1.0f;
		worldTransform3_.scale_.x -= 1.0f;
	}

	if (Flag2) {
		worldTransform3_.translation_.x += 1.0f;
		worldTransform3_.scale_.x -= 1.0f;
	}
	worldTransform_.UpdateMatrix();
	worldTransform2_.UpdateMatrix();
	worldTransform3_.UpdateMatrix();
	worldTransform4_.UpdateMatrix();
}

void Electricity::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
	model2_->Draw(worldTransform2_, *viewProjection_, &objColor);
	

}
//左用

void Electricity::OnCollision() {
	Flag = true;
}

AABB Electricity::GetAABB() { 
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

//右側

void Electricity::OnCollision2() {
	Flag2 = true;
}

AABB Electricity::GetAABB2() {
	KamataEngine::Vector3 worldPos = worldTransform2_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}
