#pragma once
#include <assert.h>
#include <cmath>

struct Matrix4x4;

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {

	static const int kColumnWidth = 60;

	float x;
	float y;
	float z;

	// 加算
	Vector3 Add(const Vector3& v1, const Vector3& v2) {
		return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	}
	Vector3 operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	// 減算
	Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
		return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	}

	// スカラー倍
	Vector3 Multiply(float scalar, const Vector3& v) {
		return {scalar * v.x, scalar * v.y, scalar * v.z};
	}

	// 内積
	float Dot(const Vector3& v1, const Vector3& v2) {
		return {v1.x * v2.x + v1.y * v2.y + v1.z * v2.z};
	}

	// 長さ（ノルム）
	float Length(const Vector3& v) { return {std::sqrt(Dot(v, v))}; }

	// 正規化
	Vector3 Normalize(const Vector3& v) {

		Vector3 tmpVector3 = {0, 0, 0};

		if (Length(v) != 0) {
			tmpVector3.x = v.x / Length(v);
			tmpVector3.y = v.y / Length(v);
			tmpVector3.z = v.z / Length(v);
		}

		return tmpVector3;
	}

	// 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	// ベクトル変換
	static Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);

};