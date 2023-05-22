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

// 透視投影行列
Matrix4x4 Matrix4x4::MakePerspectiveFovMatrix(
    float fovY, float aspectRatio, float nearClip, float farClip) {
	return {
	    1 / aspectRatio * (1 / tanf(fovY / 2)),
	    0,
	    0,
	    0,
	    0,
	    1 / tanf(fovY / 2),
	    0,
	    0,
	    0,
	    0,
	    farClip / (farClip - nearClip),
	    1,
	    0,
	    0,
	    (-nearClip * farClip) / (farClip - nearClip),
	    0};
}

// 正射影行列
Matrix4x4 Matrix4x4::MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float nearClip, float farClip) {
	return {
	    2.0f / (right - left),
	    0,
	    0,
	    0,
	    0,
	    2.0f / (top - bottom),
	    0,
	    0,
	    0,
	    0,
	    1 / (farClip - nearClip),
	    0,
	    (left + right) / (left - right),
	    (top + bottom) / (bottom - top),
	    nearClip / (nearClip - farClip),
	    1};
}

// ビューポート変換行列
Matrix4x4 Matrix4x4::MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth) {
	float w = width / 2.0f;
	float h = height / 2.0f;
	return {w, 0, 0, 0, 0, -h, 0, 0, 0, 0, maxDepth - minDepth, 0, left + w, top + h, minDepth, 1};
}

Vector3 Matrix4x4::GetTranslate() const { return {m[3][0], m[3][1], m[3][2]}; };
