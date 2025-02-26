#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
#include"AABB.h"
class Player;
class Door1;
class Electricity {
public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Model*model2, KamataEngine::Camera* viewProjection);
	
	void Update();

	void Draw();

	void OnCollision(const Player* player);
	
	// AABBを取得
	AABB GetAABB();
	Door1* GetDoor1() { return door; }
	

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;
	

	KamataEngine::WorldTransform worldTransform_;
	//KamataEngine::WorldTransform worldTransform2_;
	
	KamataEngine::ObjectColor objColor = {};
	bool Flag;
	KamataEngine::Vector3 kSpeed = {1.0f, 0.0f, 0.0f};

	Door1* door=nullptr ;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};
