#include "Electricity.h"

void Electricity::Initialize(KamataEngine::Model* model, KamataEngine::Model* model2, KamataEngine::Model* model3, KamataEngine::Model* model4, KamataEngine::Camera* viewProjection) {
	model_ = model;//プレイヤーが触る板用
	model2_ = model2;
	model3_ = model3;//動くところ用
	model4_ = model4;

	worldTransform_.Initialize();//プレイヤーが触る板用
	worldTransform2_.Initialize();
	worldTransform3_.Initialize();//動くところ用
	worldTransform4_.Initialize();

	viewProjection_ = viewProjection;
	objColor.Initialize();

}

void Electricity::Update() {

}

void Electricity::Draw() {}
