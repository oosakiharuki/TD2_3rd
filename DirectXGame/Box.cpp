#include "Box.h"
#include"math/Vector3.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include "math/MathUtility.h"

using namespace KamataEngine::MathUtility;

void Box::Initialize(KamataEngine::Model* model, KamataEngine::Camera* viewProjection, KamataEngine::Vector3 position) {

	viewProjection_ = viewProjection;
	model_ = model;
	objColor.Initialize();
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Box::Update() {
	if (Flag) {
		if (20.0f > worldTransform_.translation_.y) {

			worldTransform_.translation_.y += kSpeed;
		}
	}


    if (mode_ == Mode::Normal) { 
		// 通常の押す処理 
		worldTransform_.translation_ += velocity_; 
	} else if (mode_ == Mode::Hop) { 
		// 飛ばす処理
		worldTransform_.translation_ += velocity_; 
		// 減衰効果を追加して徐々に減速 
		velocity_ *= 0.98f; 
	}

	worldTransform_.UpdateMatrix();
}

void Box::Draw() { model_->Draw(worldTransform_, *viewProjection_, &objColor); }

void Box::ApplyForce(const KamataEngine::Vector3& force) { 
	velocity_ += force * kSpeed; }
