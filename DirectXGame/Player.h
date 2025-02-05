#pragma once 
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "input/Input.h"
#include"AABB.h"

class Electricity;
class Electricity2;
class Door1;
class Door2;

class Player {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, int playerId);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera *camera);

    KamataEngine::Vector3 GetWorldPosition();

	void SetWorldPosition(const KamataEngine::Vector3& position);
	void SetStarrPosition(const KamataEngine::Vector3& position);

	void ResetPosition() { worldTransform_.translation_ = startPosition_; }
	void ReSetHp() { HP = 3; }
	// AABBを取得
	AABB GetAABB();
	void OnCollision(const Electricity* electricity);
	void OnCollision2(const Electricity2* electricity2);
	void OnCollisionBullet();
	float GetRadius() { return radius_; }

	void PlayerUpdateMatrix() { worldTransform_.UpdateMatrix(); }
	bool IsGetDead() { return IsDead; }

private:
	KamataEngine::Input* input_ = nullptr;
	XINPUT_STATE state, preState;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Vector3 startPosition_ = {0.0f, 0.0f, 0.0f};

	KamataEngine::Model* model_ = nullptr;
	float radius_ = 1.0f;
	float moveSpeed_;
	// プレイヤーの速度
	KamataEngine::Vector3 playerVelocity;
	bool IsDead=false;
	int HP = 3;
	int playerId_;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
};