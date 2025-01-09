#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
#include"AABB.h"

class Electricity {
public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Model*model2,KamataEngine::Model*model3,KamataEngine::Model*model4, KamataEngine::Camera* viewProjection);

	void Update();

	void Draw();

	void OnCollision();
	// AABBを取得
	AABB GetAABB();

	void OnCollision2();
	// AABBを取得
	AABB GetAABB2();

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;
	KamataEngine::Model* model3_ = nullptr;
	KamataEngine::Model* model4_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::WorldTransform worldTransform2_;
	KamataEngine::WorldTransform worldTransform3_;
	KamataEngine::WorldTransform worldTransform4_;
	KamataEngine::ObjectColor objColor = {};
	bool Flag;
	bool Flag2;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};
