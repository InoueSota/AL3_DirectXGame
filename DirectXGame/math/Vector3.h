#pragma once
#include <assert.h>
#include <cmath>
#include <vector>

struct Matrix4x4;

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {

	static const int kColumnWidth = 60;

	float x;
	float y;
	float z;

	/// <summary>
	/// 比較
	/// </summary>
	friend bool operator==(const Vector3& vec1, const Vector3& vec2);

	/// <summary>
	/// 加算
	/// </summary>
	static Vector3 Add(const Vector3& v1, const Vector3& v2);
	friend Vector3& operator+=(Vector3& vec1, const Vector3& vec2);
	friend Vector3 operator+(const Vector3& vec1, const Vector3& vec2);

	/// <summary>
	/// 減算
	/// </summary>
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator-(const Vector3& vec1, const Vector3& vec2);
	friend Vector3 operator-(const Vector3& vec);

	/// <summary>
	/// スカラー倍
	/// </summary>
	static Vector3 Multiply(float scalar, const Vector3& v);
	friend Vector3 operator*(const Vector3& vec1, const Vector3& vec2);
	friend Vector3 operator*(const Vector3& vec, float scalar);
	friend Vector3 operator*(int scalar, const Vector3& vec);

	/// <summary>
	/// 除算
	/// </summary>
	friend Vector3 operator/(const Vector3& vec, float scalar);

	/// <summary>
	/// 内積
	/// </summary>
	static float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// クロス積(外積)
	/// </summary>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 長さ(ノルム)：平方根を求める
	/// </summary>
	static float Length(const Vector3& v);

	/// <summary>
	/// 長さ(ノルム)：平方根を求めない
	/// </summary>
	static float LengthSquare(const Vector3& v);

	/// <summary>
	/// 正規化
	/// </summary>
	static Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 垂直なベクトルを１つ求める
	/// </summary>
	static Vector3 Perpendicular(const Vector3& vector);

	/// <summary>
	/// 正射影ベクトルを求める
	/// </summary>
	static Vector3 Project(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 座標変換
	/// </summary>
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// ベクトル変換
	/// </summary>
	static Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);

	static Vector3 GetXaxis(const Matrix4x4& m);
	static Vector3 GetYaxis(const Matrix4x4& m);
	static Vector3 GetZaxis(const Matrix4x4& m);

	/// <summary>
	/// 線形補間
	/// </summary>
	static Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
	static float Lerp(const float f1, const float f2, float t);

	/// <summary>
	/// 球面線形補間
	/// </summary>
	static Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

	/// <summary>
	/// Catmull-Rom補間
	/// </summary>
	static Vector3 CatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t);

};