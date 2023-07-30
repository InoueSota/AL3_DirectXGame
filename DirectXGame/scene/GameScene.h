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

	// シーン
	enum Scene {
		Title,
		Ingame,
		Result
	};
	Scene scene = Title;

	/// <summary>
	/// フェード処理
	/// </summary>
	bool Fade();

private: 


	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t bgm_;

	// テクスチャハンドル
	uint32_t textureHandle_[7];
	uint32_t enemytextureHandle_[10];

	// タイトル
	uint32_t titleTextureHandle_[2];
	Sprite* title_[2];
	Vector2 titlePosition_;
	float theta;

	// リザルト
	uint32_t resultTextureHandle_[4];
	Sprite* result_[4];
	Vector2 resultPosition_;
	float theta2;
	int deathCount_;

	// スプライト類（主にUI）
	uint32_t ui_base_ = 0;
	uint32_t left = 0;
	uint32_t right = 0;
	uint32_t up = 0;
	uint32_t down = 0;
	uint32_t space = 0;
	Sprite* s_ui_base_ = nullptr;
	Sprite* s_left = nullptr;
	Sprite* s_right = nullptr;
	Sprite* s_up = nullptr;
	Sprite* s_down = nullptr;
	Sprite* s_space = nullptr;
	
	// 3Dモデルデータ
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelBullet_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelEnemyBullet_ = nullptr;
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

	int frame;

	// 当たり判定
	ColliderManager* colliderManager_ = nullptr;
	
	// デバッグカメラ有効
	bool isDebugCameraActive = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	uint32_t u_black;
	Sprite* s_black;
	bool isStartFadeIn;
	bool isStartFadeOut;
	float alphaT;
	float alpha;
};
