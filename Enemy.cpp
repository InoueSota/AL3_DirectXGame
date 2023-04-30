#include "Enemy.h"
#include "EnemyBullet.h"
#include <cassert>
#include "BaseEnemyState.h"


Enemy::Enemy() {
	
	// 行動遷移
	state_ = new EnemyStateApproach();
}
Enemy::~Enemy() {
	
	// 行動遷移の解放
	delete state_;
}

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

	// 移動初期化関数
	MoveInitialize();

}

void Enemy::Update() {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		if (bullet->IsDead()) {
			return true;
		}
		return false;
	});
	
	// 終了したタイマーを削除
	timedCalls_.remove_if([](std::unique_ptr<TimedCall>& timedCall) {
		if (timedCall->IsFinished()) {
			return true;
		}
		return false;
	});

	state_->Update(this);

	// 弾更新
	for (std::list<std::unique_ptr<EnemyBullet>>::iterator it = bullets_.begin(); it != bullets_.end(); ++it) {
		(*it)->Update();
	}

	// 他フェーズに以降する時はこの処理をしないようにする
	for (std::list<std::unique_ptr<TimedCall>>::iterator it = timedCalls_.begin(); it != timedCalls_.end(); ++it) {
		(*it)->Update();
	}

	// WorldTransformの更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (std::list<std::unique_ptr<EnemyBullet>>::iterator it = bullets_.begin(); it != bullets_.end(); ++it) {
		(*it)->Draw(viewProjection);
	}
}

void Enemy::ChangeState(BaseEnemyState* newState) {

	// 状態遷移
	delete state_;
	state_ = newState;
}

void Enemy::MoveInitialize() {
	// 発射タイマーをセットする
	FireAndReset();
}

void Enemy::Move(const Vector3& vector) {

	// 受け取った引数分、敵を動かす
	worldTransform_.translation_ += vector;
}

void Enemy::Fire() {

	// 弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	// 速度ベクトルを目標の向きに合わせて回転させる
	velocity = Vector3::TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	std::unique_ptr<EnemyBullet>newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾を登録する
	bullets_.push_back(std::move(newBullet));
}

void Enemy::FireAndReset() {

	// 弾を発射
	Fire();
	// 発射タイマーをセットする
	timedCalls_.push_back(std::move(std::make_unique<TimedCall>(std::bind(&Enemy::FireAndReset, this), kFireInterval)));
}
