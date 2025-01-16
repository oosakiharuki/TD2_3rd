#pragma once
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/ObjectColor.h>
#include <3d/WorldTransform.h>

class Box {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection,KamataEngine::Vector3 position);

	void Update();

	void Draw();

	KamataEngine::Vector3 GetCenter() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
	void SetWorldPosition(KamataEngine::Vector3 position) { worldTransform_.translation_ = position; }

	void ApplyForce(const KamataEngine::Vector3& force);

	enum class Mode {
		Normal,
		Hop,
	};

	void SetMode(Mode mode) { mode_ = mode; }

	Mode GetNowMode() const { return mode_; }

	KamataEngine::Vector3 GetWorldPosition();

	private:

	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor = {};

	float kSpeed = 0.2f;
	bool Flag;

	float radius_ = 1.0f;
	KamataEngine::Vector3 velocity_ = {0.0f, 0.0f, 0.0f};

	Mode mode_ = Mode::Normal;
};
