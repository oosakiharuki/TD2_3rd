#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4x4.h"
#include <cmath>

KamataEngine::Matrix4x4 Multiply(KamataEngine::Matrix4x4 m1, KamataEngine::Matrix4x4 m2);
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);

