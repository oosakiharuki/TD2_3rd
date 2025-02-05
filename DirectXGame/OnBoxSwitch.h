#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>
#include "AABB.h"

class OnBoxSwitch {
public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Camera* viewProjection,KamataEngine::Vector3 position);
	void Update();
	void Draw();
	AABB GetAABB();
	void OnCollision();
	void NoBox();
	bool GetOnBox() { return onFlag; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_;

	bool onFlag = false;
	
	// 当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};