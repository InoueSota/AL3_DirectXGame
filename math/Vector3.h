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
	Vector3 Add(const Vector3& v1, const Vector3& v2) { return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}; }
	Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y, z + other.z }; }
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
	Vector3 operator-(const Vector3& other) const { return {x - other.x, y - other.x, z - other.x}; }

	// 乗算
	Vector3 Multiply(float scalar, const Vector3& v) { return {scalar * v.x, scalar * v.y, scalar * v.z}; }
	Vector3 operator*(float scalar) { return Multiply(scalar, {x ,y, z}); }
	Vector3 operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// 除算
	Vector3 operator/(float f) const { return {x / f, y / f, z / f}; }

	// 内積
	float Dot(const Vector3& v1, const Vector3& v2) const {
		return {v1.x * v2.x + v1.y * v2.y + v1.z * v2.z};
	}

	// 長さ（ノルム）
	float Length() const { return std::sqrt(Dot({x, y, z}, {x, y, z})); }

	// 正規化
	Vector3 Normalize() const {

		if (Length() != 0.0f) {
			return *this / Length();
		} else {
			return *this;
		}
	}

	// 線形補間
	Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
		return v1 + (v2 - v1) * t;
	}
	float Lerp(const float f1, const float f2, float t) {
		return f1 + (f2 - f1) * t;
	}

	// 球面線形補間
	Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
		float s = Lerp(v1.Length(), v2.Length(), t);
		Vector3 nv1 = v1.Normalize();
		Vector3 nv2 = v2.Normalize();
		float theta = 1 / std::cos(Dot(nv1, nv2));

		return ((nv1 * std::sin((1 - t) * theta) + nv2 * std::sin(t * theta)) / std::sin(theta)) * s;
	}

	// 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	// ベクトル変換
	static Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);
};