#include "TimedCall.h"



TimedCall::TimedCall(std::function<void(const WorldTransform* parent)> function, uint32_t time) : f(function), time_(time), isFinished_(false) {}

void TimedCall::Update(const WorldTransform* parent) {

	if (isFinished_) {
		return;
	}
	time_--;
	if (time_ <= 0) {
		isFinished_ = true;
		// コールバック関数呼び出し
		f(parent);
	}
}