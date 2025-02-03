#pragma once
#include "3d/WorldTransform.h"
#include "3d/Model.h"
#include "3d/Camera.h"

/// <summary>
/// パーティクル
/// </summary>
class Particle {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Draw();

	bool IsActive() const { return isActive_; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {0.0f, 0.0f, 0.0f};
	// パーティクルの寿命
	float lifetime_ = 1.0f;
	// 経過時間
	float timer_ = 0.0f;
	bool isActive_ = true;
};