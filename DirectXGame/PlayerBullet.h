#pragma once
#include "Player.h"
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Collider.h"



/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet : public Player {
public:
	PlayerBullet();
	~PlayerBullet();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="parent">親</param>
	/// <param name="position">初期座標</param>
	/// <param name="target">狙う座標</param>
	void Initialize(Model* model, const WorldTransform* parent, const Vector3& position, const Vector3& target);

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
	const Vector3& GetWorldPosition() const override { return worldTransform_.translation_; }

	/// <summary>
	/// 衝突時に呼ばれる関数
	/// </summary>
	void OnCollision() override { isDead_ = true; };

	/// <summary>
	/// 親となるWorldTransformをセット
	/// </summary>
	/// <param name="parent">親となるWorldTransform</param>
	void SetParent(const WorldTransform* parent);

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
};

