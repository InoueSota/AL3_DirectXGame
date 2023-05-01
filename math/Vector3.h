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
	Vector3 operator-(const Vector3& other) { return Subtract({x, y, z}, other); }

	// スカラー倍
	Vector3 Multiply(float scalar, const Vector3& v) {
		return {scalar * v.x, scalar * v.y, scalar * v.z};
	}
	Vector3 operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// 内積
	float Dot(const Vector3& v1, const Vector3& v2) {
		return {v1.x * v2.x + v1.y * v2.y + v1.z * v2.z};
	}

	// 長さ（ノルム）
	float Length() { return std::sqrt(Dot({x, y, z}, {x, y, z})); }

	// 正規化
	Vector3 Normalize() {

		if (Length() != 0) {
			x = x / Length();
			y = y / Length();
			z = z / Length();
		}
		return *this;
	}

	// 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	// ベクトル変換
	static Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);
};