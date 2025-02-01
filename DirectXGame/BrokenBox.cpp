#include "BrokenBox.h"
#include <cassert>
#include "Box.h"

BrokenBox::~BrokenBox() {
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}

void BrokenBox::Initialize(KamataEngine::Model* model, KamataEngine::Model* modelParticlel, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position) {
	assert(model);
	model_ = model;
	assert(modelParticlel);
	modelParticle_ = modelParticlel;;

	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	objColor.Initialize();

}

void BrokenBox::Update() { 
	worldTransform_.UpdateMatrix();

	// パーティクルの更新
	for (Particle* particle : particles_) {
		particle->Update();
	}

	// 破壊後の処理
	if (isBreak) {
		// パーティクルを一定数まで生成
		if (particleCount_ < particleLimit_) {
			for (int i = 0; i < 5; i++) {
				if (particleCount_ >= particleLimit_)
					break;

				Particle* particle = new Particle();
				particle->Initialize(modelParticle_, viewProjection_, worldTransform_.translation_);
				particles_.push_back(particle);
				particleCount_++;
			}
		}

		// 無効なパーティクルを削除
		particles_.remove_if([](Particle* particle) {
			if (!particle->IsActive()) {
				delete particle;
				return true;
			}
			return false;
		});
	}
}

void BrokenBox::Draw() { 
	if (!isBreak) {
    	model_->Draw(worldTransform_, *viewProjection_, &objColor); 
	}

	// パーティクルの描画
	for (Particle* particle : particles_) {
		particle->Draw();
	}
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
