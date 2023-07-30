#include "Various.h"


Various::Various() {

}
Various::~Various() {

}



// 範囲内の数値をランダムに返す（int型）
int Various::Random(int min, int max) { return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX)); }

// 範囲内の数値をランダムに返す（float型）
float Various::Random(float min, float max) { return min + (float)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX)); }

// ランダムを使用するなら宣言必須
void Various::Srand() { srand((unsigned)time(NULL)); }

