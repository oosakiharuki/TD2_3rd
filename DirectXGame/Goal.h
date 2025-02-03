#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>

class Goal {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3 position);

	void Update();

	void Draw();

	KamataEngine::Vector3 GetWorldPosition();

	float GetRadius() const { return radius_; }

private:
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor = {};

	float radius_ = 1.0f;
};