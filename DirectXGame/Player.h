#pragma once 
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "input/Input.h"

class MapChip;

class Player {
public:
	// 初期化
	void Initialize(KamataEngine::Vector3 startPosition, KamataEngine::Model* model, int playerId, MapChip* mapChip);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera *camera);

    KamataEngine::Vector3 GetWorldPosition();

	void SetWorldPosition(const KamataEngine::Vector3& position);

	// 境界ボックスを更新
	void UpdateBoundingBox();

	// 衝突判定
	bool CheckCollision(const KamataEngine::Vector3& minA, const KamataEngine::Vector3& maxA, const KamataEngine::Vector3& minB, const KamataEngine::Vector3& maxB) {
		return (minA.x <= maxB.x && maxA.x >= minB.x) && (minA.y <= maxB.y && maxA.y >= minB.y) && (minA.z <= maxB.z && maxA.z >= minB.z);
	}

private:
	KamataEngine::Input* input_ = nullptr;
	XINPUT_STATE state, preState;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	float moveSpeed_;
	// プレイヤーの速度
	KamataEngine::Vector3 playerVelocity;

	int playerId_;

	MapChip* mapChip_ = nullptr;

	KamataEngine::Vector3 boundingBoxMin_;
	KamataEngine::Vector3 boundingBoxMax_;
};