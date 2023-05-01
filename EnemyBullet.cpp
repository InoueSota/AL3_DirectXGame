#include "EnemyBullet.h"



EnemyBullet::EnemyBullet() : isDead_(false) {}
EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	// Z方向に伸びた形状
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	// Y軸周り角度（θy）
	worldTransform_.rotation_.y = std::atan2(velocity.x, velocity.z);
	float velocityXZ = std::sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
	// X軸周り角度（θx）
	worldTransform_.rotation_.x = std::atan2(-velocity.y, velocityXZ);

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void EnemyBullet::Update() {

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