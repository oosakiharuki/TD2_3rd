#pragma once
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include"AABB.h"
class Player;
class Box;

class MapWall {
public:

	void Initialize(KamataEngine::Model* model, uint32_t texture, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position);
	void Update();
	void Draw();
	AABB GetAABB();
	void OnCollisionPlayer(Player* player, AABB aabb);
	void OnCollisionBox(Box* box, AABB aabb);
	void SetCorrectionPos(Player* player);
	KamataEngine::Vector3 GetWorldPosition() { return worldTransform_.translation_; }

	void Resetcorrection() { correctionPos = {0, 0, 0}; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* viewProjection_;
	KamataEngine::Model* model_ = nullptr;
	uint32_t textureHandle = 0u;

	//当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

	KamataEngine::Vector3 correctionPos;

	Rect rect;
};