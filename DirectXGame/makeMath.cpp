#include"makeMath.h"
#include<cmath>
#include<assert.h>


// 単項演算子オーバーロード
KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v) { return v; }
KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v) { return KamataEngine::Vector3(-v.x, -v.y, -v.z); }
KamataEngine::Vector3& operator+=(KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;
	return lhv;
}
KamataEngine::Vector3& operator-=(KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv) {
	lhv.x -= rhv.x;
	lhv.y -= rhv.y;
	lhv.z -= rhv.z;
	return lhv;
}
KamataEngine::Vector3& operator*=(KamataEngine::Vector3& v, float s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}
KamataEngine::Vector3& operator/=(KamataEngine::Vector3& v, float s) {
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return v;
}
// 2項演算子オーバーロード
const KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2) {
	KamataEngine::Vector3 temp(v1);
	return temp += v2;
}
const KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2) {
	KamataEngine::Vector3 temp(v1);
	return temp -= v2;
}
const KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v, float s) {
	KamataEngine::Vector3 temp(v);
	return temp *= s;
}
const KamataEngine::Vector3 operator*(float s, const KamataEngine::Vector3& v) { return v * s; }
const KamataEngine::Vector3 operator/(const KamataEngine::Vector3& v, float s) {
	KamataEngine::Vector3 temp(v);
	return temp /= s;
}

// 行列の掛け算
KamataEngine::Matrix4x4 MatrixMultiply(KamataEngine::Matrix4x4& m1, KamataEngine::Matrix4x4& m2) {

	KamataEngine::Matrix4x4 result;
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return result;
}

KamataEngine::Matrix4x4 MakeRotateZMatrix(float& rot) {
	KamataEngine::Matrix4x4 RotateMatZ = {0};
	RotateMatZ = {std::cos(rot), std::sin(rot), 0, 0, -std::sin(rot), std::cos(rot), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	return RotateMatZ;
}

KamataEngine::Vector3 Transform(const KamataEngine::Vector3& vector, const KamataEngine::Matrix4x4& matrix) {

	KamataEngine::Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rot, const KamataEngine::Vector3& translate) {

	KamataEngine::Matrix4x4 ScallMat, RotateMat, RotateMatX, RotateMatY, RotateMatZ, TranslateMat, returnMat;

	// スケール行列作成
	ScallMat = {scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1};

	// XYZ回転行列作成
	RotateMatX = {1, 0, 0, 0, 0, cosf(rot.x), sinf(rot.x), 0, 0, -sinf(rot.x), cosf(rot.x), 0, 0, 0, 0, 1};

	RotateMatY = {cosf(rot.y), 0, -sinf(rot.y), 0, 0, 1, 0, 0, sinf(rot.y), 0, cosf(rot.y), 0, 0, 0, 0, 1};

	RotateMatZ = {cosf(rot.z), sinf(rot.z), 0, 0, -sinf(rot.z), cosf(rot.z), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	// XYZ回転行列の合成(Z*X*Y)
	RotateMat = MatrixMultiply(RotateMatZ, RotateMatX);
	// ↑の結果＊Y軸回転
	RotateMat = MatrixMultiply(RotateMat, RotateMatY);

	// 平行移動行列作成
	TranslateMat = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, translate.x, translate.y, translate.z, 1};

	// スケール＊回転＊平行移動をワールド変換行列に
	returnMat = MatrixMultiply(ScallMat, RotateMat);
	returnMat = MatrixMultiply(returnMat, TranslateMat);

	return returnMat;
}
KamataEngine::Vector3 TransformNormal(const KamataEngine::Vector3& v, const KamataEngine::Matrix4x4& m) {
	KamataEngine::Vector3 result{v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0], v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1], v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};
	return result;
}
float Length(const KamataEngine::Vector3& v) {
	float v2 = 0;
	v2 = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return v2;
}

KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v) {
	KamataEngine::Vector3 v2 = {0};
	v2.x = v.x / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	v2.y = v.y / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	v2.z = v.z / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return v2;
}