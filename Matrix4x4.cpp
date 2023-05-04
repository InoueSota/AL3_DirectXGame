#include "Matrix4x4.h"
#include "Vector3.h"



// 平行移動行列
Matrix4x4 Matrix4x4::MakeTranslateMatrix(const Vector3& translate) {
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translate.x, translate.y, translate.z, 1
	};
}

// 拡大縮小行列
Matrix4x4 Matrix4x4::MakeScaleMatrix(const Vector3& scale) {
	return {
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1,
	};
}

// 3次元アフィン変換行列
Matrix4x4 Matrix4x4::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	// 回転行列を求める
	Matrix4x4 rotateMatrix = Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));

	// 拡縮行列をかける
	Matrix4x4 scaleRotateMatrix = Multiply(MakeScaleMatrix(scale), rotateMatrix);

	// 平行移動行列をかける
	Matrix4x4 affineMatrix = Multiply(scaleRotateMatrix, MakeTranslateMatrix(translate));

	return affineMatrix;
}

Vector3 Matrix4x4::GetTranslate() const { return {m[3][0], m[3][1], m[3][2]}; };
