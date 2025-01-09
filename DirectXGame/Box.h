#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>

class Box {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection);

	void Update();

	void Draw();

	KamataEngine::Vector3 GetCenter() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }

	void ApplyForce(const KamataEngine::Vector3& force);

	private:

	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor = {};

	float kSpeed = 0.5f;
	bool Flag;

	float radius_;
};
