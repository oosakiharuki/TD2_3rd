#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
#include "Particle.h"
#include"AABB.h"
class Player;
class Box;

class BrokenBox {
public:
	~BrokenBox();

	void Initialize(KamataEngine::Model* model, KamataEngine::Model* modelParticlel, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position);

	void Update();

	void Draw();

	KamataEngine::Vector3 GetWorldPosition();

	float GetRadius() const { return radius_; }

	void OnCollision();

	void SetBoxes(const std::list<Box*>& boxes) { boxes_ = boxes; }

	bool IsBreak() const { return isBreak; }
	AABB GetAABB();
	void OnCollisionPlayer(Player* player, AABB aabb);
	void OnCollisionBox(Box* box, AABB aabb);
	void SetCorrectionPos(Player* player);
	void Resetcorrection() { correctionPos = {0, 0, 0}; }

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor = {};

	bool isBreak = false;
	float radius_ = 1.0f;
	std::list<Box*> boxes_;

	std::list<Particle*> particles_;
	KamataEngine::Model* modelParticle_ = nullptr;

    // パーティクルの最大生成数
	int particleLimit_ = 5; 
    // 現在の生成済みパーティクル数
    int particleCount_ = 0;  

	// 当たり判定サイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

	Rect rect;
	KamataEngine::Vector3 correctionPos;
};
