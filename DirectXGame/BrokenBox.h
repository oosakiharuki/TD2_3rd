#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>
class BrokenBox {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection);

	void Update();

	void Draw();

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor = {};
	bool flag;
};
