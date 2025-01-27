#include "Gate.h"
#include <algorithm>

using namespace KamataEngine;

void Gate::Initialize(Model* model, Camera* viewProjection, Vector3 position) {
	model_ = model;
	viewProjection_ = viewProjection;

	objColor.Initialize();
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	closePos = position;
	openPos = {position.x, position.y, position.z + 3.0f};

	
}


void Gate::Update() {
	worldTransform_.UpdateMatrix();

	if (isOpenFlag) {
		worldTransform_.translation_.z += 0.1f;
	} else if (closeGate) {
		worldTransform_.translation_.z -= 0.1f;
	}

	worldTransform_.translation_.z = std::clamp(worldTransform_.translation_.z, closePos.z, openPos.z);
}

void Gate::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_, &objColor);
}

void Gate::OpenGate() { isOpenFlag = true; }

void Gate::CloseGate() { isOpenFlag = false; }


void Gate::Pairing(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
