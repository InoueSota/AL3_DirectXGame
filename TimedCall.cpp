#include "TimedCall.h"



TimedCall::TimedCall(std::function<void(void)> function, uint32_t time) : f(function), time_(time), isFinished_(false) {}

void TimedCall::Update() {

	if (isFinished_) {
		return;
	}
	time_--;
	if (time_ <= 0) {
		isFinished_ = true;
		// コールバック関数呼び出し
		f();
	}
}