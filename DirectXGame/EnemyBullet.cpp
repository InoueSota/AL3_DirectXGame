#include "EnemyBullet.h"
#include "Player.h"
#include "CollisionConfig.h"



EnemyBullet::EnemyBullet() : isDead_(false) {}
EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const WorldTransform* parent, const Vector3& targetPosition) {

	// NULLポインタチェック
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("enemy/enemy.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 狙うエリアの座標を取得する
	targetPosition_ = targetPosition;

	const float kBulletSpeed = 1.0f;

	// 球面線形補間により、今の速度と自キャラへのベクトルを内挿し、新たな速度とする
	velocity_ = (targetPosition_ - worldTransform_.translation_);
	// ベクトルを正規化する
	velocity_ = velocity_.Normalize(velocity_) * kBulletSpeed;

	// レールカメラに追従させる
	SetParent(parent);

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributeEnemy);
	// 衝突対象を自分の属性以外に設定
	SetCollisionMask(~kCollisionAttributeEnemy);
}

void EnemyBullet::Update()
{
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ += velocity_;

	// WorldTransformの更新
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

// 親となるWorldTransformをセット
void EnemyBullet::SetParent(const WorldTransform* parent) {

	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}