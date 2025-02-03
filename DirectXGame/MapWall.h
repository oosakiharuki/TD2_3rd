#pragma once
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include"AABB.h"
class Player;

struct Rect {
	KamataEngine::Vector2 leftTop;
	KamataEngine::Vector2 rightTop;
	KamataEngine::Vector2 leftBottom;
	KamataEngine::Vector2 rightBottom;
};

class MapWall {
public:

	void Initialize(KamataEngine::Model* model, uint32_t texture, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position);
	void Update();
	void Draw();
	void OnCollision(Player* player,AABB aabb);
	AABB GetAABB();
	void SetHeight() { isHeight = true; }
	void SetWidth() {isWidth = true; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* viewProjection_;
	KamataEngine::Model* model_ = nullptr;
	uint32_t textureHandle = 0u;

	//当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

	// 当たり判定用のサイズ
	float sizeX = 1;
	float sizeY = 1;

	Rect rect;
	float left = 0;
	float right = 0;
	float top = 0;
	float bottom = 0;

	bool isHeight = false;
	bool isWidth = false;
};