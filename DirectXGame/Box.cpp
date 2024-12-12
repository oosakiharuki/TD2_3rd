#include "Box.h"
#include"math/Vector3.h"

void Box::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection) {

	viewProjection_ = viewProjection;
	model_ = model;
	objColor.Initialize();
	worldTransform_.Initialize();
}

void Box::Update() {

}

void Box::Draw() {}
