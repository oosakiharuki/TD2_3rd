#include "CameraController.h"
#include "Rope.h"
#include "3d/WorldTransform.h"
#include "makeMath.h"

using namespace KamataEngine;

void CameraController::Initialize() {

	viewProjection_.Initialize();
	//CameraController::Rect cameraArea = {10.0f, 100 - 10.0f, 6.0f, 6.0f};
}

void CameraController::Update() {
	
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform(); 

	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;

	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() {
	
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;

}
