#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
#include "Particle.h"

class Box;

class BrokenBox {
public:
	~BrokenBox();

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection);

	void Update();

	void Draw();

	KamataEngine::Vector3 GetWorldPosition();

	void OnCollision();

	void SetBoxes(const std::list<Box*>& boxes) { boxes_ = boxes; }

	bool IsBreak() const { return isBreak; }

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor = {};

	bool isBreak = false;

	std::list<Box*> boxes_;

	std::list<Particle*> particles_;
	KamataEngine::Model* modelParticle_ = nullptr;

    // パーティクルの最大生成数
	int particleLimit_ = 5; 
    // 現在の生成済みパーティクル数
    int particleCount_ = 0;  

};
