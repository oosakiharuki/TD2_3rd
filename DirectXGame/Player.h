#pragma once 
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "input/Input.h"
#include"AABB.h"


class Player {
public:
	// 初期化
	void Initialize(KamataEngine::Vector3 startPosition, KamataEngine::Model* model, int playerId);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera *camera);

    KamataEngine::Vector3 GetWorldPosition();

	void SetWorldPosition(const KamataEngine::Vector3& position);

private:
	KamataEngine::Input* input_ = nullptr;
	XINPUT_STATE state, preState;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	float moveSpeed_;
	// プレイヤーの速度
	KamataEngine::Vector3 playerVelocity;

	int playerId_;
};