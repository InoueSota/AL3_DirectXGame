#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"



class BaseEnemyState;

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	Enemy();
	~Enemy();

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

	/*
	// 行動フェーズ
	enum class Phase {
		Approach,	// 接近する
		Leave		// 離脱する
	};

	// フェーズ
	Phase phase_ = Phase::Approach;

	// 接近関数
	void Approach();
	// 離脱する
	void Leave();

	// 行動関数ポインタ
	static void (Enemy::*spPhaseFunc[])();
	*/

	// 行動遷移
	BaseEnemyState* state_ = nullptr;

	// 速度
	Vector3 velocity_;
};
