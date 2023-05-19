#pragma once

#include "Enemy.h"
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Collider.h"

class Player;

/// <summary>
/// 敵キャラの弾
/// </summary>
class EnemyBullet : public Enemy {
public:
	EnemyBullet();
	~EnemyBullet();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション（参照渡し）</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 弾の寿命が尽きたかの判定
	/// </summary>
	inline bool IsDead() const { return isDead_; }

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	const Vector3& GetWorldPosition() const { return worldTransform_.translation_; }

	/// <summary>
	/// プレイヤーのポインタを共有する
	/// </summary>
	void SetPlayer(std::unique_ptr<Player> player) { player_ = std::move(player); }

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision() { isDead_ = true; };

	///// <summary>
	///// 衝突時に呼ばれる関数
	///// </summary>
	//void OnCollision() override;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_;

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;

	// 自キャラのポインタ
	std::unique_ptr<Player> player_;
};

