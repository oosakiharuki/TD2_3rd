#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
#include"AABB.h"
class Player;
class Electricity {
public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Model*model2, KamataEngine::Camera* viewProjection);
	
	void Update();

	void Draw();

	void OnCollision(const Player* player);
	// AABBを取得
	AABB GetAABB();

	

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;
	

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::WorldTransform worldTransform2_;
	
	KamataEngine::ObjectColor objColor = {};
	bool Flag;
	
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};
