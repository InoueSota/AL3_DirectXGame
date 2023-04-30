#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "TimedCall.h"
#include <list>
#include <functional>


class EnemyBullet;
class BaseEnemyState;

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	Enemy();
	~Enemy();

	// 発射間隔
	static const int kFireInterval = 60;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">速度</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

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
	/// 行動遷移
	/// </summary>
	void ChangeState(BaseEnemyState* newState);

	/// <summary>
	/// 移動
	/// </summary>
	void Move(const Vector3& vector);

	/// <summary>
	/// 移動初期化
	/// </summary>
	void MoveInitialize();

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	/// <summary>
	/// 弾を発射し、タイマーをリセットするコールバック関数
	/// </summary>
	void FireAndReset();

	/// <summary>
	/// 現在座標の取得
	/// </summary>
	inline Vector3 GetEnemyPosition() { return worldTransform_.translation_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	// 発射タイマー
	int32_t fireTimer_ = 0;
	// 時限発動のリスト
	std::list<std::unique_ptr<TimedCall>> timedCalls_;

	// 行動遷移
	BaseEnemyState* state_ = nullptr;

	// 速度
	Vector3 velocity_;
};
