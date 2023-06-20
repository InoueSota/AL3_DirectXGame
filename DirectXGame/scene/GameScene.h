#pragma once

#include "PrimitiveDrawer.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "RailCamera.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Skydome.h"
#include "DebugCamera.h"
#include <sstream>
#include "Collider.h"
#include "ColliderManager.h"
#include <vector>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(GameScene* gameScene);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void ChackAllCollisions();

	/// <summary>
	/// 敵を発生させる
	/// </summary>
	void MakeEnemy(const Vector3& position, GameScene* gameScene);

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands(GameScene* gameScene);

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void DrawCatmullRomSpline();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t reticleTextureHandle_ = 0;
	uint32_t textureHandle_ = 0;
	// 3Dモデルデータ
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;

	// 線描画
	PrimitiveDrawer* primitiveDrawer_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// レールカメラ
	std::unique_ptr<RailCamera> railCamera_;
	// スプライン曲線制御点（通過点）
	std::vector<Vector3> controlPoints_;
	// 天球
	std::unique_ptr<Skydome> skyDome_;
	// 自キャラ
	std::unique_ptr<Player> player_;
	// 敵キャラ
	std::list<std::unique_ptr<Enemy>> enemy_;
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	bool isWait_ = false;
	int32_t interval_ = 0;

	// 当たり判定
	ColliderManager* colliderManager_ = nullptr;
	
	// デバッグカメラ有効
	bool isDebugCameraActive = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

};
