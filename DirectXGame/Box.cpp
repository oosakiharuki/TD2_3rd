#include "Box.h"
#include"math/Vector3.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include "math/MathUtility.h"

using namespace KamataEngine::MathUtility;

void Box::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection) {

	viewProjection_ = viewProjection;
	model_ = model;
	objColor.Initialize();
	worldTransform_.Initialize();

	radius_ = 1.0f;
}

void Box::Update() {
	if (Flag) {
		if (20.0f > worldTransform_.translation_.y) {

			worldTransform_.translation_.y += kSpeed;
		}
	}

	worldTransform_.UpdateMatrix();
}

void Box::Draw() { model_->Draw(worldTransform_, *viewProjection_, &objColor); }

void Box::ApplyForce(const KamataEngine::Vector3& force) { 
	worldTransform_.translation_ += force; 
}
