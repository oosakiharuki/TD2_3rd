#include "3d/WorldTransform.h"
#include "makeMath.h"
void KamataEngine::WorldTransform::UpdateMatrix() {

	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	TransferMatrix();
}