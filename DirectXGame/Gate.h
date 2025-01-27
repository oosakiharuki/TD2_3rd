#pragma once
#include "makeMath.h"
#include "MapChip.h"

class Gate{
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position);
	void Update();
	void Draw();

	void OpenGate();
	void CloseGate();

	const KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }
	void Pairing(const KamataEngine::WorldTransform* parent);

private:
	KamataEngine::Camera* viewProjection_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor = {};

	KamataEngine::Vector3 closePos = {};
	KamataEngine::Vector3 openPos = {};

	bool isOpenFlag = false;
	bool closeGate = true;
	KamataEngine::Vector2 open;

	bool onSide = true;
	bool onVartical = false;
};