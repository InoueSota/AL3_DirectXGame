#pragma once
#include <functional>
#include <WorldTransform.h>

class TimedCall {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TimedCall(std::function<void(const WorldTransform* parent)> function, uint32_t time);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const WorldTransform* parent);

	/// <summary>
	/// 完了ならtrueを返す
	/// </summary>
	inline bool IsFinished() const { return isFinished_; }

private:

	// コールバック
	std::function<void(const WorldTransform* parent)> f;

	// 残り時間
	uint32_t time_;

	// 完了フラグ
	bool isFinished_ = false;

};

