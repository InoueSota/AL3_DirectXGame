#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>


GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルデータの解放
	delete model_;
	delete modelSkydome_;

	// デバッグカメラの解放
	delete debugCamera_;

	// 自キャラの解放
	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	reticleTextureHandle_ = TextureManager::Load("reticle.png");
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデルデータの生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("aurora", true);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// レールカメラの初期化
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize({0.0f, 0.0f, -50.0f}, 0.0f);

	// 天球の初期化
	skyDome_ = std::make_unique<Skydome>();
	skyDome_->Initialize(modelSkydome_);

	// 自キャラの初期化
	player_ = new Player();
	player_->SetParent(&railCamera_->GetWorldTransform());
	player_->Initialize(model_, textureHandle_, reticleTextureHandle_);

	// 敵発生データの読み込み
	LoadEnemyPopData();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update(GameScene* gameScene) {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		if (bullet->IsDead()) {
			return true;
		}
		return false;
	});
	// デスフラグの立った敵を削除
	enemy_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		if (enemy->IsDead()) {
			return true;
		}
		return false;
	});

	// レールカメラの更新
	railCamera_->Update();

	// 天球の更新
	skyDome_->Update();
	
	// 自キャラの更新
	player_->Update(viewProjection_);

	// 敵キャラ
	UpdateEnemyPopCommands(gameScene);

	// 敵キャラの更新
	for (std::list<std::unique_ptr<Enemy>>::iterator it = enemy_.begin(); it != enemy_.end(); ++it) {
		if ((*it)) {
			(*it)->Update();
		}
	}
	// 弾更新
	for (std::list<std::unique_ptr<EnemyBullet>>::iterator bullet = bullets_.begin();
	     bullet != bullets_.end(); ++bullet) {
		(*bullet)->Update();
	}

	// 衝突判定と応答
	ChackAllCollisions();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		isDebugCameraActive = true;
	}
	if (isDebugCameraActive) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}

#endif
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// 天球の描画
	skyDome_->Draw(viewProjection_);

	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 敵キャラの描画
	for (std::list<std::unique_ptr<Enemy>>::iterator it = enemy_.begin(); it != enemy_.end(); ++it) {
		for (std::list<std::unique_ptr<EnemyBullet>>::iterator bullet = bullets_.begin(); bullet != bullets_.end(); ++bullet) {
			(*bullet)->Draw(viewProjection_);
		}
		(*it)->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::ChackAllCollisions() {

	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

	#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (std::list<std::unique_ptr<EnemyBullet>>::iterator bullet = bullets_.begin(); bullet != bullets_.end(); ++bullet) {
		// 敵弾の座標
		posB = (*bullet)->GetWorldPosition();

		// 座標AとBの距離を求める
		float direction = (std::powf(posA.x - posB.x, 2.0f) + std::powf(posA.y - posB.y, 2.0f) + std::powf(posA.z - posB.z, 2.0f));

		// 球と球の交差判定
		if (direction <= std::powf(2.0f, 2.0f)) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			(*bullet)->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラの座標
	for (std::list<std::unique_ptr<Enemy>>::iterator enemy = enemy_.begin(); enemy != enemy_.end(); ++enemy) {
		// 敵キャラの座標
		posA = (*enemy)->GetWorldPosition();

		// 自キャラと自弾全ての当たり判定
		for (std::list<std::unique_ptr<PlayerBullet>>::iterator bullet = playerBullets.begin(); bullet != playerBullets.end(); ++bullet) {
			// 自弾の座標
			posB = (*bullet)->GetWorldPosition();

			// 座標AとBの距離を求める
			float direction = (std::powf(posA.x - posB.x, 2.0f) + std::powf(posA.y - posB.y, 2.0f) + std::powf(posA.z - posB.z, 2.0f));

			// 球と球の交差判定
			if (direction <= std::powf(2.0f, 2.0f)) {
				// 敵キャラの衝突時コールバックを呼び出す
				(*enemy)->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
				(*bullet)->OnCollision();
			}
		}
	}
	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定

	// 自弾の座標
	for (std::list<std::unique_ptr<PlayerBullet>>::iterator playerbullet = playerBullets.begin(); playerbullet != playerBullets.end(); ++playerbullet) {
		posA = (*playerbullet)->GetWorldPosition();

		// 自弾と敵弾全ての当たり判定
		for (std::list<std::unique_ptr<EnemyBullet>>::iterator enemybullet = bullets_.begin(); enemybullet != bullets_.end(); ++enemybullet) {
			// 自弾の座標
			posB = (*enemybullet)->GetWorldPosition();

			// 座標AとBの距離を求める
			float direction = (std::powf(posA.x - posB.x, 2.0f) + std::powf(posA.y - posB.y, 2.0f) + std::powf(posA.z - posB.z, 2.0f));

			// 球と球の交差判定
			if (direction <= std::powf(2.0f, 2.0f)) {
				// 敵キャラの衝突時コールバックを呼び出す
				(*playerbullet)->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
				(*enemybullet)->OnCollision();
			}
		}
	}
	#pragma endregion
}

void GameScene::MakeEnemy(const Vector3& position, GameScene* gameScene) {
	// 敵キャラの生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	// 敵キャラに自キャラのアドレスを渡す
	newEnemy->SetPlayer(player_);
	// 敵キャラの初期化
	newEnemy->Initialize(model_, position, {0.0f, 0.0f, 0.0f}, gameScene);
	// 敵キャラを登録する
	enemy_.push_back(std::move(newEnemy));
}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
	// リストに登録する
	bullets_.push_back(std::move(enemyBullet));
}

void GameScene::LoadEnemyPopData() {

	// ファイルを開く
	std::ifstream file;
	file.open("Resources./enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands(GameScene* gameScene) {

	// 待機処理
	if (isWait_) {
		interval_--;
		if (interval_ <= 0) {
			// 待機完了
			isWait_ = false;
		}
		return;
	}
	
	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// X座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// Y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// Z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			MakeEnemy(Vector3(x, y, z), gameScene);
		} else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			isWait_ = true;
			interval_ = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}