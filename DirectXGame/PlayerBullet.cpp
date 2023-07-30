#include "PlayerBullet.h"
#include <cassert>
#include "CollisionConfig.h"



PlayerBullet::PlayerBullet() {}
PlayerBullet::~PlayerBullet() {}

void PlayerBullet::Initialize(Model* model, const WorldTransform* parent, const Vector3& position, const Vector3& target) {

	// NULLポインタチェック
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("player/player.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 速度
	const float kBulletSpeed = 1.0f;

	// 初期化段階で向きを取得しその方向にずっと進むようにする
	velocity_ = (target - worldTransform_.translation_);
	// ベクトルを正規化する
	velocity_ = velocity_.Normalize(velocity_) * kBulletSpeed;

	// 進行方向に見た目の回転を合わせる
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	float velocityXZ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ);

	// レールカメラに追従させる
	SetParent(parent);

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributePlayer);
	// 衝突対象を自分の属性以外に設定
	SetCollisionMask(~kCollisionAttributePlayer);
}

void PlayerBullet::Update() 
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

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::SetParent(const WorldTransform* parent) 
{
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
