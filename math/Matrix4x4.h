#pragma once
#include <assert.h>
#include <cmath>



struct Vector3;

/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {

	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;

	float m[4][4];

	// 加算
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
		return {
			m1.m[0][0] + m2.m[0][0],
			m1.m[0][1] + m2.m[0][1],
			m1.m[0][2] + m2.m[0][2],
			m1.m[0][3] + m2.m[0][3],
			m1.m[1][0] + m2.m[1][0],
			m1.m[1][1] + m2.m[1][1],
			m1.m[1][2] + m2.m[1][2],
			m1.m[1][3] + m2.m[1][3],
			m1.m[2][0] + m2.m[2][0],
			m1.m[2][1] + m2.m[2][1],
			m1.m[2][2] + m2.m[2][2],
			m1.m[2][3] + m2.m[2][3],
			m1.m[3][0] + m2.m[3][0],
			m1.m[3][1] + m2.m[3][1],
			m1.m[3][2] + m2.m[3][2],
			m1.m[3][3] + m2.m[3][3]
		};
	}

	// 減算
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
		return {
			m1.m[0][0] - m2.m[0][0],
			m1.m[0][1] - m2.m[0][1],
			m1.m[0][2] - m2.m[0][2],
			m1.m[0][3] - m2.m[0][3],
			m1.m[1][0] - m2.m[1][0],
			m1.m[1][1] - m2.m[1][1],
			m1.m[1][2] - m2.m[1][2],
			m1.m[1][3] - m2.m[1][3],
			m1.m[2][0] - m2.m[2][0],
			m1.m[2][1] - m2.m[2][1],
			m1.m[2][2] - m2.m[2][2],
			m1.m[2][3] - m2.m[2][3],
			m1.m[3][0] - m2.m[3][0],
			m1.m[3][1] - m2.m[3][1],
			m1.m[3][2] - m2.m[3][2],
			m1.m[3][3] - m2.m[3][3]
		};
	}

	// 積
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
		return {
		    m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
			m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
			m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
			m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],
			m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
			m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
			m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
			m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],
			m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
			m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
			m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
			m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],
			m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
			m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
			m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
			m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3]
		};
	}
	Matrix4x4 operator*(const Matrix4x4& m1) {
	return {
			m1.m[0][0] * m[0][0] + m1.m[0][1] * m[1][0] + m1.m[0][2] * m[2][0] + m1.m[0][3] * m[3][0],
			m1.m[0][0] * m[0][1] + m1.m[0][1] * m[1][1] + m1.m[0][2] * m[2][1] + m1.m[0][3] * m[3][1],
			m1.m[0][0] * m[0][2] + m1.m[0][1] * m[1][2] + m1.m[0][2] * m[2][2] + m1.m[0][3] * m[3][2],
			m1.m[0][0] * m[0][3] + m1.m[0][1] * m[1][3] + m1.m[0][2] * m[2][3] + m1.m[0][3] * m[3][3],
			m1.m[1][0] * m[0][0] + m1.m[1][1] * m[1][0] + m1.m[1][2] * m[2][0] + m1.m[1][3] * m[3][0],
			m1.m[1][0] * m[0][1] + m1.m[1][1] * m[1][1] + m1.m[1][2] * m[2][1] + m1.m[1][3] * m[3][1],
			m1.m[1][0] * m[0][2] + m1.m[1][1] * m[1][2] + m1.m[1][2] * m[2][2] + m1.m[1][3] * m[3][2],
			m1.m[1][0] * m[0][3] + m1.m[1][1] * m[1][3] + m1.m[1][2] * m[2][3] + m1.m[1][3] * m[3][3],
			m1.m[2][0] * m[0][0] + m1.m[2][1] * m[1][0] + m1.m[2][2] * m[2][0] + m1.m[2][3] * m[3][0],
			m1.m[2][0] * m[0][1] + m1.m[2][1] * m[1][1] + m1.m[2][2] * m[2][1] + m1.m[2][3] * m[3][1],
			m1.m[2][0] * m[0][2] + m1.m[2][1] * m[1][2] + m1.m[2][2] * m[2][2] + m1.m[2][3] * m[3][2],
			m1.m[2][0] * m[0][3] + m1.m[2][1] * m[1][3] + m1.m[2][2] * m[2][3] + m1.m[2][3] * m[3][3],
			m1.m[3][0] * m[0][0] + m1.m[3][1] * m[1][0] + m1.m[3][2] * m[2][0] + m1.m[3][3] * m[3][0],
			m1.m[3][0] * m[0][1] + m1.m[3][1] * m[1][1] + m1.m[3][2] * m[2][1] + m1.m[3][3] * m[3][1],
			m1.m[3][0] * m[0][2] + m1.m[3][1] * m[1][2] + m1.m[3][2] * m[2][2] + m1.m[3][3] * m[3][2],
			m1.m[3][0] * m[0][3] + m1.m[3][1] * m[1][3] + m1.m[3][2] * m[2][3] + m1.m[3][3] * m[3][3]
		};
	}
	Matrix4x4 operator*=(const Matrix4x4& m1) {
		m[0][0] *= m1.m[0][0] * m[0][0] + m1.m[0][1] * m[1][0] + m1.m[0][2] * m[2][0] + m1.m[0][3] * m[3][0];
		m[0][1] *= m1.m[0][0] * m[0][1] + m1.m[0][1] * m[1][1] + m1.m[0][2] * m[2][1] + m1.m[0][3] * m[3][1];
		m[0][2] *= m1.m[0][0] * m[0][2] + m1.m[0][1] * m[1][2] + m1.m[0][2] * m[2][2] + m1.m[0][3] * m[3][2];
		m[0][3] *= m1.m[0][0] * m[0][3] + m1.m[0][1] * m[1][3] + m1.m[0][2] * m[2][3] + m1.m[0][3] * m[3][3];
		m[1][0] *= m1.m[1][0] * m[0][0] + m1.m[1][1] * m[1][0] + m1.m[1][2] * m[2][0] + m1.m[1][3] * m[3][0];
		m[1][1] *= m1.m[1][0] * m[0][1] + m1.m[1][1] * m[1][1] + m1.m[1][2] * m[2][1] + m1.m[1][3] * m[3][1];
		m[1][2] *= m1.m[1][0] * m[0][2] + m1.m[1][1] * m[1][2] + m1.m[1][2] * m[2][2] + m1.m[1][3] * m[3][2];
		m[1][3] *= m1.m[1][0] * m[0][3] + m1.m[1][1] * m[1][3] + m1.m[1][2] * m[2][3] + m1.m[1][3] * m[3][3];
		m[2][0] *= m1.m[2][0] * m[0][0] + m1.m[2][1] * m[1][0] + m1.m[2][2] * m[2][0] + m1.m[2][3] * m[3][0];
		m[2][1] *= m1.m[2][0] * m[0][1] + m1.m[2][1] * m[1][1] + m1.m[2][2] * m[2][1] + m1.m[2][3] * m[3][1];
		m[2][2] *= m1.m[2][0] * m[0][2] + m1.m[2][1] * m[1][2] + m1.m[2][2] * m[2][2] + m1.m[2][3] * m[3][2];
		m[2][3] *= m1.m[2][0] * m[0][3] + m1.m[2][1] * m[1][3] + m1.m[2][2] * m[2][3] + m1.m[2][3] * m[3][3];
		m[3][0] *= m1.m[3][0] * m[0][0] + m1.m[3][1] * m[1][0] + m1.m[3][2] * m[2][0] + m1.m[3][3] * m[3][0];
		m[3][1] *= m1.m[3][0] * m[0][1] + m1.m[3][1] * m[1][1] + m1.m[3][2] * m[2][1] + m1.m[3][3] * m[3][1];
		m[3][2] *= m1.m[3][0] * m[0][2] + m1.m[3][1] * m[1][2] + m1.m[3][2] * m[2][2] + m1.m[3][3] * m[3][2];
		m[3][3] *= m1.m[3][0] * m[0][3] + m1.m[3][1] * m[1][3] + m1.m[3][2] * m[2][3] + m1.m[3][3] * m[3][3];
		return *this;
	}

	// 逆行列
	static Matrix4x4 Inverse(const Matrix4x4& m1) {
		float det = 1 / (m1.m[0][0] * m1.m[1][1] * m1.m[2][2] * m1.m[3][3] +
						 m1.m[0][0] * m1.m[1][2] * m1.m[2][3] * m1.m[3][1] +
						 m1.m[0][0] * m1.m[1][3] * m1.m[2][1] * m1.m[3][2] -
						 m1.m[0][0] * m1.m[1][3] * m1.m[2][2] * m1.m[3][1] -
						 m1.m[0][0] * m1.m[1][2] * m1.m[2][1] * m1.m[3][3] -
						 m1.m[0][0] * m1.m[1][1] * m1.m[2][3] * m1.m[3][2] -
						 m1.m[0][1] * m1.m[1][0] * m1.m[2][2] * m1.m[3][3] -
						 m1.m[0][2] * m1.m[1][0] * m1.m[2][3] * m1.m[3][1] -
						 m1.m[0][3] * m1.m[1][0] * m1.m[2][1] * m1.m[3][2] +
						 m1.m[0][3] * m1.m[1][0] * m1.m[2][2] * m1.m[3][1] +
						 m1.m[0][2] * m1.m[1][0] * m1.m[2][1] * m1.m[3][3] +
						 m1.m[0][1] * m1.m[1][0] * m1.m[2][3] * m1.m[3][2] +
						 m1.m[0][1] * m1.m[1][2] * m1.m[2][0] * m1.m[3][3] +
						 m1.m[0][2] * m1.m[1][3] * m1.m[2][0] * m1.m[3][1] +
						 m1.m[0][3] * m1.m[1][1] * m1.m[2][0] * m1.m[3][2] -
						 m1.m[0][3] * m1.m[1][2] * m1.m[2][0] * m1.m[3][1] -
						 m1.m[0][2] * m1.m[1][1] * m1.m[2][0] * m1.m[3][3] -
						 m1.m[0][1] * m1.m[1][3] * m1.m[2][0] * m1.m[3][2] -
						 m1.m[0][1] * m1.m[1][2] * m1.m[2][3] * m1.m[3][0] -
						 m1.m[0][2] * m1.m[1][3] * m1.m[2][1] * m1.m[3][0] -
						 m1.m[0][3] * m1.m[1][1] * m1.m[2][2] * m1.m[3][0] +
						 m1.m[0][3] * m1.m[1][2] * m1.m[2][1] * m1.m[3][0] +
						 m1.m[0][2] * m1.m[1][1] * m1.m[2][3] * m1.m[3][0] +
						 m1.m[0][1] * m1.m[1][3] * m1.m[2][2] * m1.m[3][0]);
		assert(det != 0.0f);
		Matrix4x4 tmp{
		    det * ( m1.m[1][1] * m1.m[2][2] * m1.m[3][3] + m1.m[1][2] * m1.m[2][3] * m1.m[3][1] + m1.m[1][3] * m1.m[2][1] * m1.m[3][2] - m1.m[1][3] * m1.m[2][2] * m1.m[3][1] - m1.m[1][2] * m1.m[2][1] * m1.m[3][3] - m1.m[1][1] * m1.m[2][3] * m1.m[3][2]),
		    det * (-m1.m[0][1] * m1.m[2][2] * m1.m[3][3] - m1.m[0][2] * m1.m[2][3] * m1.m[3][1] - m1.m[0][3] * m1.m[2][1] * m1.m[3][2] + m1.m[0][3] * m1.m[2][2] * m1.m[3][1] + m1.m[0][2] * m1.m[2][1] * m1.m[3][3] + m1.m[0][1] * m1.m[2][3] * m1.m[3][2]),
		    det * ( m1.m[0][1] * m1.m[1][2] * m1.m[3][3] + m1.m[0][2] * m1.m[1][3] * m1.m[3][1] + m1.m[0][3] * m1.m[1][1] * m1.m[3][2] - m1.m[0][3] * m1.m[1][2] * m1.m[3][1] - m1.m[0][2] * m1.m[1][1] * m1.m[3][3] - m1.m[0][1] * m1.m[1][3] * m1.m[3][2]),
		    det * (-m1.m[0][1] * m1.m[1][2] * m1.m[2][3] - m1.m[0][2] * m1.m[1][3] * m1.m[2][1] - m1.m[0][3] * m1.m[1][1] * m1.m[2][2] + m1.m[0][3] * m1.m[1][2] * m1.m[2][1] + m1.m[0][2] * m1.m[1][1] * m1.m[2][3] + m1.m[0][1] * m1.m[1][3] * m1.m[2][2]),
		    det * (-m1.m[1][0] * m1.m[2][2] * m1.m[3][3] - m1.m[1][2] * m1.m[2][3] * m1.m[3][0] - m1.m[1][3] * m1.m[2][0] * m1.m[3][2] + m1.m[1][3] * m1.m[2][2] * m1.m[3][0] + m1.m[1][2] * m1.m[2][0] * m1.m[3][3] + m1.m[1][0] * m1.m[2][3] * m1.m[3][2]),
		    det * ( m1.m[0][0] * m1.m[2][2] * m1.m[3][3] + m1.m[0][2] * m1.m[2][3] * m1.m[3][0] + m1.m[0][3] * m1.m[2][0] * m1.m[3][2] - m1.m[0][3] * m1.m[2][2] * m1.m[3][0] - m1.m[0][2] * m1.m[2][0] * m1.m[3][3] - m1.m[0][0] * m1.m[2][3] * m1.m[3][2]),
		    det * (-m1.m[0][0] * m1.m[1][2] * m1.m[3][3] - m1.m[0][2] * m1.m[1][3] * m1.m[3][0] - m1.m[0][3] * m1.m[1][0] * m1.m[3][2] + m1.m[0][3] * m1.m[1][2] * m1.m[3][0] + m1.m[0][2] * m1.m[1][0] * m1.m[3][3] + m1.m[0][0] * m1.m[1][3] * m1.m[3][2]),
		    det * ( m1.m[0][0] * m1.m[1][2] * m1.m[2][3] + m1.m[0][2] * m1.m[1][3] * m1.m[2][0] + m1.m[0][3] * m1.m[1][0] * m1.m[2][2] - m1.m[0][3] * m1.m[1][2] * m1.m[2][0] - m1.m[0][2] * m1.m[1][0] * m1.m[2][3] - m1.m[0][0] * m1.m[1][3] * m1.m[2][2]),
		    det * ( m1.m[1][0] * m1.m[2][1] * m1.m[3][3] + m1.m[1][1] * m1.m[2][3] * m1.m[3][0] + m1.m[1][3] * m1.m[2][0] * m1.m[3][1] - m1.m[1][3] * m1.m[2][1] * m1.m[3][0] - m1.m[1][1] * m1.m[2][0] * m1.m[3][3] - m1.m[1][0] * m1.m[2][3] * m1.m[3][1]),
		    det * (-m1.m[0][0] * m1.m[2][1] * m1.m[3][3] - m1.m[0][1] * m1.m[2][3] * m1.m[3][0] - m1.m[0][3] * m1.m[2][0] * m1.m[3][1] + m1.m[0][3] * m1.m[2][1] * m1.m[3][0] + m1.m[0][1] * m1.m[2][0] * m1.m[3][3] + m1.m[0][0] * m1.m[2][3] * m1.m[3][1]),
		    det * ( m1.m[0][0] * m1.m[1][1] * m1.m[3][3] + m1.m[0][1] * m1.m[1][3] * m1.m[3][0] + m1.m[0][3] * m1.m[1][0] * m1.m[3][1] - m1.m[0][3] * m1.m[1][1] * m1.m[3][0] - m1.m[0][1] * m1.m[1][0] * m1.m[3][3] - m1.m[0][0] * m1.m[1][3] * m1.m[3][1]),
		    det * (-m1.m[0][0] * m1.m[1][1] * m1.m[2][3] - m1.m[0][1] * m1.m[1][3] * m1.m[2][0] - m1.m[0][3] * m1.m[1][0] * m1.m[2][1] + m1.m[0][3] * m1.m[1][1] * m1.m[2][0] + m1.m[0][1] * m1.m[1][0] * m1.m[2][3] + m1.m[0][0] * m1.m[1][3] * m1.m[2][1]),
		    det * (-m1.m[1][0] * m1.m[2][1] * m1.m[3][2] - m1.m[1][1] * m1.m[2][2] * m1.m[3][0] - m1.m[1][2] * m1.m[2][0] * m1.m[3][1] + m1.m[1][2] * m1.m[2][1] * m1.m[3][0] + m1.m[1][1] * m1.m[2][0] * m1.m[3][2] + m1.m[1][0] * m1.m[2][2] * m1.m[3][1]),
		    det * ( m1.m[0][0] * m1.m[2][1] * m1.m[3][2] + m1.m[0][1] * m1.m[2][2] * m1.m[3][0] + m1.m[0][2] * m1.m[2][0] * m1.m[3][1] - m1.m[0][2] * m1.m[2][1] * m1.m[3][0] - m1.m[0][1] * m1.m[2][0] * m1.m[3][2] - m1.m[0][0] * m1.m[2][2] * m1.m[3][1]),
		    det * (-m1.m[0][0] * m1.m[1][1] * m1.m[3][2] - m1.m[0][1] * m1.m[1][2] * m1.m[3][0] - m1.m[0][2] * m1.m[1][0] * m1.m[3][1] + m1.m[0][2] * m1.m[1][1] * m1.m[3][0] + m1.m[0][1] * m1.m[1][0] * m1.m[3][2] + m1.m[0][0] * m1.m[1][2] * m1.m[3][1]),
		    det * ( m1.m[0][0] * m1.m[1][1] * m1.m[2][2] + m1.m[0][1] * m1.m[1][2] * m1.m[2][0] + m1.m[0][2] * m1.m[1][0] * m1.m[2][1] - m1.m[0][2] * m1.m[1][1] * m1.m[2][0] - m1.m[0][1] * m1.m[1][0] * m1.m[2][2] - m1.m[0][0] * m1.m[1][2] * m1.m[2][1]),
		};
		return tmp;
	}

	// 転置行列
	static Matrix4x4 Transpose(const Matrix4x4& m1) {
		return {
			m1.m[0][0], m1.m[1][0], m1.m[2][0], m1.m[3][0],
			m1.m[0][1], m1.m[1][1], m1.m[2][1], m1.m[3][1],
			m1.m[0][2], m1.m[1][2], m1.m[2][2], m1.m[3][2],
			m1.m[0][3], m1.m[1][3], m1.m[2][3], m1.m[3][3]
		};
	}

	// 単位行列の作成
	static Matrix4x4 MakeIdentity4x4() {
		return {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	// 平行移動行列
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	// 拡大縮小行列
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	// X軸回転行列
	static Matrix4x4 MakeRotateXMatrix(float radian) {
		float s = std::sin(radian);
		float c = std::cos(radian);
		return {
				1,  0, 0, 0,
				0,  c, s, 0,
				0, -s, c, 0,
				0,  0, 0, 1
		};
	}

	// Y軸回転行列
	static Matrix4x4 MakeRotateYMatrix(float radian) {
		float s = std::sin(radian);
		float c = std::cos(radian);
		return {
				c, 0, -s, 0,
				0, 1,  0, 0,
				s, 0,  c, 0,
				0, 0,  0, 1
		};
	}

	// Z軸回転行列
	static Matrix4x4 MakeRotateZMatrix(float radian) {
		float s = std::sin(radian);
		float c = std::cos(radian);
		return {
				 c, s, 0, 0,
				-s, c, 0, 0,
				 0, 0, 1, 0,
				 0, 0, 0, 1
		};
	}

	// 3次元アフィン変換行列
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	// 取得
	Vector3 GetTranslate() const;

};
