#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include <functional>
#include <memory>
#include "Collider.h"
#include "RailCamera.h"
#include "Various.h"
#include "Sprite.h"


// 前方宣言
class EnemyBullet;
class GameScene;
class BaseEnemyState;
class Player;

/// <summary>
/// 敵
/// </summary>
class Enemy : public Collider {
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
	void Initialize(Model* model, Model* bulletModel, const Vector3& position, const Vector3& velocity, GameScene* gameScene, const WorldTransform* parent, RailCamera* railCamera, uint32_t textureHandle[4]);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const WorldTransform* parent);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション（参照渡し）</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	/// <summary>
	/// 行動遷移
	/// </summary>
	void ChangeState(BaseEnemyState* newState);

	/// <summary>
	/// 移動
	/// </summary>
	void Move(const Vector3& vector);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire(const WorldTransform* parent, Vector3& bulletTarget);

	/// <summary>
	/// 現在座標の取得
	/// </summary>
	inline Vector3 GetEnemyPosition() { return worldTransform_.translation_; }

	/// <summary>
	/// プレイヤーのポインタを共有する
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	const Vector3& GetWorldPosition() const override { return worldTransform_.translation_; }

	/// <summary>
	/// 弾の寿命が尽きたかの判定
	/// </summary>
	inline bool IsDead() const { return isDead_; }

	/// <summary>
	/// ゲームシーンのポインタを共有する
	/// </summary>
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	/// <summary>
	/// 衝突時に呼ばれる関数
	/// </summary>
	void OnCollision() override { hp--; };

	/// <summary>
	/// 親となるWorldTransformをセット
	/// </summary>
	/// <param name="parent">親となるWorldTransform</param>
	void SetParent(const WorldTransform* parent);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// レールカメラのワールド変換データ
	RailCamera* railCamera_;
	// モデル
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ゲームシーン
	GameScene* gameScene_ = nullptr;

	// 行動遷移
	BaseEnemyState* state_ = nullptr;
	// 行動が変わっていないか
	bool isChangeState_ = false;
	// デスフラグ
	bool isDead_ = false;
	// 体力
	int hp;

	int bullet_1;
	int bullet_2;
	int bullet_3;
	int beforeFire_;
	int interval_;
	bool isStart;

	// 速度
	Vector3 velocity_;

	// 毎フレーム加算
	int frame;

	Vector3 targetPosition_[9];
	Vector3 bulletTarget_[3];

	// 自キャラ
	Player* player_;

	Sprite* red[9];
};
