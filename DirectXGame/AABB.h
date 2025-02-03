#pragma once
#include"math/Vector3.h"
#include"math/Vector2.h"

struct AABB {
	KamataEngine::Vector3 min;
	KamataEngine::Vector3 max;

	static bool IsCollision(const AABB& aabb1, const AABB& aabb2);
};

struct Rect {
	KamataEngine::Vector2 leftTop;
	KamataEngine::Vector2 rightTop;
	KamataEngine::Vector2 leftBottom;
	KamataEngine::Vector2 rightBottom;
};