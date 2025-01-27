#pragma once
#include "AABB.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
#include"Door2.h"

class Player;
class Electricity2 {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Camera* viewProjection);

	void Update();

	void Draw();

	void OnCollision(const Player* player);
	// AABBを取得
	AABB GetAABB();
	Door2* GetDoor2() { return door; }
	

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;
	

	KamataEngine::WorldTransform worldTransform_;
	Door2* door = nullptr;

	KamataEngine::ObjectColor objColor = {};
	bool Flag;
	KamataEngine::Vector3 kSpeed = {1.0f, 0.0f, 0.0f};
	
	
	
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};