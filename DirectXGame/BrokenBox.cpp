#include "BrokenBox.h"
#include <cassert>
#include "Box.h"

void BrokenBox::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection) {
	assert(model);
	model_ = model;

	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = KamataEngine::Vector3{10.0f, -10.0f, 0.0f};
	objColor.Initialize();
}

void BrokenBox::Update() { worldTransform_.UpdateMatrix(); }

void BrokenBox::Draw() { 
	if (!isBreak) {
    	model_->Draw(worldTransform_, *viewProjection_, &objColor); }
	}


KamataEngine::Vector3 BrokenBox::GetWorldPosition() { 
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド座標の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void BrokenBox::OnCollision() {
	for (Box* box : boxes_) {
		if (box->GetNowMode() == Box::Mode::Hop) {
			isBreak = true;
		}
	}
}
