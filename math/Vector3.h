#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {

	static const int kColumnWidth = 60;

	float x;
	float y;
	float z;

	//加算
	Vector3 Add(const Vector3& v1, const Vector3& v2) {
		return {
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z
		};
	}

	//減算
	Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
		return {
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z
		};
	}

	//スカラー倍
	Vector3 Multiply(float scalar, const Vector3& v) {
		return {
			scalar * v.x,
			scalar * v.y,
			scalar * v.z
		};
	}

	//内積
	float Dot(const Vector3& v1, const Vector3& v2) {
		return {
			v1.x * v2.x + v1.y * v2.y + v1.z * v2.z
		};
	}

	////長さ（ノルム）
	//float Length(const Vector3& v) {

	//}

	////正規化
	//Vector3 Normalize(const Vector3& v) {

	//}

	////表示
	//void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

};