#include "3d/WorldTransform.h"
#include "MyMath.h"
void KamataEngine::WorldTransform::UpdateMatrix() {

	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	TransferMatrix();
}