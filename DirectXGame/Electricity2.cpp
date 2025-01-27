#include "Electricity2.h"
#include"Player.h"
#include"makeMath.h"

void Electricity2::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* viewProjection) {
	model_ = model; // プレイヤーが触る板用
	model2_ = model2;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize(); // プレイヤーが触る板用
	door = new Door2();
	door->Initialize(model2_, viewProjection_, kSpeed);

	objColor.Initialize();
}

void Electricity2::Update() {
	door->Update();
	worldTransform_.UpdateMatrix();
	
}

void Electricity2::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
	door->Draw();
}

void Electricity2::OnCollision(const Player* player) { 
	(void)player;
	Flag = true; 
	door->SetFlag(Flag);
}

AABB Electricity2::GetAABB() {
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}
