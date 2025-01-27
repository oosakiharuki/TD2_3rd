#include "Electricity.h"
#include"Player.h"
#include"Door1.h"

void Electricity::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* viewProjection) {
	model_ = model;//プレイヤーが触る板用
	model2_ = model2;
	viewProjection_ = viewProjection;
	door = new Door1();
	door->Initialize(model2_, viewProjection_, kSpeed);

	worldTransform_.Initialize();//プレイヤーが触る板用
	worldTransform_.translation_.y = 5.0f;

	
	
	objColor.Initialize();

	
}

void Electricity::Update() {
	
	
		door->Update();
	
	
	worldTransform_.UpdateMatrix();
	
	
	
}

void Electricity::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
	//model2_->Draw(worldTransform2_, *viewProjection_, &objColor);
	door->Draw();

}
//左用

void Electricity::OnCollision(const Player* player) { 
	(void)player;
	Flag = true;
	door->SetFlag(Flag);
}



AABB Electricity::GetAABB() { 
	KamataEngine::Vector3 worldPos = worldTransform_.translation_;
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

//右側

