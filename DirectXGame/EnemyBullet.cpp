#include "EnemyBullet.h"
#include "Player.h"
#include "CollisionConfig.h"



EnemyBullet::EnemyBullet() : isDead_(false) {}
EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, const Vector3& position) {

	// NULLポインタチェック
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("red.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	
	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributeEnemy);
	// 衝突対象を自分の属性以外に設定
	SetCollisionMask(~kCollisionAttributeEnemy);
}

void EnemyBullet::Update() {

	const float kBulletSpeed = 1.0f;

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// 敵弾から自キャラへのベクトルを計算
	Vector3 toPlayer = player_->GetWorldPosition() - worldTransform_.translation_;

	// ベクトルを正規化する
	toPlayer = toPlayer.Normalize();
	velocity_ = velocity_.Normalize();
	// 球面線形補間により、今の速度と自キャラへのベクトルを内挿し、新たな速度とする
	velocity_ = velocity_.Slerp(velocity_, toPlayer, 0.1f) * kBulletSpeed;

	// 進行方向に見た目の回転を合わせる
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	float velocityXZ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ);

	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ += velocity_;

	// WorldTransformの更新
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
