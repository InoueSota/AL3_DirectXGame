#include "Enemy.h"
#include <cassert>


Enemy::Enemy() {}
Enemy::~Enemy() {}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("gangEnemy.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

}

void (Enemy::*Enemy::spPhaseFunc[])() = {
	&Enemy::Approach,
	&Enemy::Leave
};

void Enemy::Update() {

	/*
	switch (phase_) {
	case Phase::Approach:
	default:
		Approach();
		break;
	case Phase::Leave:
		Leave();
		break;
	}
	*/

	// 行動関数ポインタに入っている関数を呼び出す
	(this->*spPhaseFunc[static_cast<size_t>(phase_)])();

	// WorldTransformの更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Approach() {
	// 移動（ベクトルを加算）
	worldTransform_.translation_ += velocity_;
	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	// 移動（ベクトルを加算）
	worldTransform_.translation_ += {velocity_.x, velocity_.y, -velocity_.z};
	// 規定の位置に到達したら接近
	if (worldTransform_.translation_.z > 20.0f) {
		phase_ = Phase::Approach;
	}
}