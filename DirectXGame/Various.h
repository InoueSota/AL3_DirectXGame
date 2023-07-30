#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Vector2.h"



class Various {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Various();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Various();

	/// <summary>
	/// 範囲内の数値をランダムに返す（int型）
	/// </summary>
	/// <param name="min">最小値（int型）</param>
	/// <param name="max">最大値（int型）</param>
	/// <returns>範囲内の数値（int型）</returns>
	static int Random(int min, int max);

	/// <summary>
	/// 範囲内の数値をランダムに返す（float型）
	/// </summary>
	/// <param name="min">最小値（float型）</param>
	/// <param name="max">最大値（float型）</param>
	/// <returns>範囲内の数値（float型）</returns>
	static float Random(float min, float max);

	/// <summary>
	/// ランダムを使用するなら宣言必須
	/// </summary>
	static void Srand();
};

