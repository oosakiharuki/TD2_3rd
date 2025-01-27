#pragma once
#include "AABB.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
class Player;
class Door1 {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 speed);

	void Update();

	void Draw();

	void OnCollision(Player* player);
	void SetFlag(bool Flag1);
	void SetPosition(KamataEngine::Vector3 position) { worldTransform_.translation_ = position; }
	KamataEngine::Vector3 GetWorldPosition() { return worldTransform_.translation_; }

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::ObjectColor objColor = {};
	bool Flag;
	KamataEngine::Vector3 kSpeed;
	// キャラクターの当たり判定サイズ
	float kWidth;
	float kHeight;
};