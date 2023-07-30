#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"
#include <cassert>
#include <list>
#include "Sprite.h"
#include "Collider.h"


class PlayerBullet;

class Player : public Collider {

public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, Model* bulletModel, uint32_t textureHandle[7]);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const ViewProjection& viewProjection, const WorldTransform* parent);

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
	/// 旋回
	/// </summary>
	void Rotate();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack(const WorldTransform* parent);

	/// <summary>
	/// リロード
	/// </summary>
	void Reload();

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition() { return worldTransform_.matWorld_.GetTranslate(); }

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	const Vector3& GetWorldPosition() const override { return worldTransform_.translation_; }

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	void SetRockOnPosition(const Vector3& enemyPosition) { rockOnPosition = enemyPosition; }

	/// <summary>
	/// 弾リストを取得
	/// </summary>
	std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	/// <summary>
	/// 親となるWorldTransformをセット
	/// </summary>
	/// <param name="parent">親となるWorldTransform</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// マウスカーソルを利用するレティクル
	/// </summary>
	void MouseCursorReticle(const ViewProjection& viewProjection);

	///// <summary>
	///// 衝突時に呼ばれる関数
	///// </summary>
	void OnCollision() override { isHit = true; };

	bool IsDead() { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// キーボード入力
	Input* input_ = nullptr;

	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;
	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;
	Sprite* bulletCount_1 = nullptr;
	Sprite* bulletCount_2 = nullptr;
	Sprite* life_[3];

	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	// 移動フラグ
	bool isMove;
	// 移動開始地点
	Vector3 basePosition;
	// 移動先地点
	Vector3 targetPosition;
	// 移動イージング変化値
	float moveT;
	// 移動イージング変化量
	float moveTmag;

	// 攻撃フラグ
	bool isStartAttack;
	// 攻撃弾数
	int attackBulletCount;
	// ロックオン座標
	Vector3 rockOnPosition;
	// 攻撃間隔
	int attackIntervalTime;

	int hp_;
	bool isHit;
	int interval;
	bool isDead_;

	// 弾を打ったかフラグ
	bool isShot;
	// リロードでこめる弾数
	const int kReloadBulletCount = 5;
	int startBulletCount;
	int endBulletCount;
	bool isStartReload;
	float reloadT;

};

