#include "Goal.h"
#include <cassert>

void Goal::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3 position) {
	assert(model);
	model_ = model;

	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	objColor.Initialize();
}

void Goal::Update() { 
	worldTransform_.UpdateMatrix(); 
}

void Goal::Draw() { 
	model_->Draw(worldTransform_, *camera_, &objColor); 
}

KamataEngine::Vector3 Goal::GetWorldPosition() { 
		// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド座標の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
