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

	// 衝突マネージャを解放
	delete colliderManager_;

	// UIの解放
	delete s_ui_base_;

	// タイトルの解放
	delete title_[0];
	delete title_[1];
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	primitiveDrawer_ = PrimitiveDrawer::GetInstance();

	bgm_ = audio_->LoadWave("BGM.wav");

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("player/player.png");
	textureHandle_[1] = TextureManager::Load("reticle.png");
	textureHandle_[2] = TextureManager::Load("number.png");
	textureHandle_[3] = TextureManager::Load("number.png");
	textureHandle_[4] = TextureManager::Load("player/1.png");
	textureHandle_[5] = TextureManager::Load("player/2.png");
	textureHandle_[6] = TextureManager::Load("player/3.png");

	enemytextureHandle_[0] = TextureManager::Load("enemy/red_1.png");
	enemytextureHandle_[1] = TextureManager::Load("enemy/red_2.png");
	enemytextureHandle_[2] = TextureManager::Load("enemy/red_3.png");
	enemytextureHandle_[3] = TextureManager::Load("enemy/red_4.png");
	enemytextureHandle_[4] = TextureManager::Load("enemy/red_5.png");
	enemytextureHandle_[5] = TextureManager::Load("enemy/red_6.png");
	enemytextureHandle_[6] = TextureManager::Load("enemy/red_7.png");
	enemytextureHandle_[7] = TextureManager::Load("enemy/red_8.png");
	enemytextureHandle_[8] = TextureManager::Load("enemy/red_9.png");
	enemytextureHandle_[9] = TextureManager::Load("enemy/hp.png");

	ui_base_ = TextureManager::Load("UI_base.png");
	left = TextureManager::Load("left.png");
	right = TextureManager::Load("right.png");
	up = TextureManager::Load("up.png");
	down = TextureManager::Load("down.png");
	space = TextureManager::Load("space.png");
	s_ui_base_ = Sprite::Create(ui_base_, Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	s_left = Sprite::Create(left, Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	s_right = Sprite::Create(right, Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	s_up = Sprite::Create(up, Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	s_down = Sprite::Create(down, Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	s_space = Sprite::Create(space, Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});

	// タイトル
	titleTextureHandle_[0] = TextureManager::Load("title/background.png");
	titleTextureHandle_[1] = TextureManager::Load("title/title.png");
	title_[0] = Sprite::Create(titleTextureHandle_[0], Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	title_[1] = Sprite::Create(titleTextureHandle_[1], Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	theta = 0.0f;
	titlePosition_ = Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f);

	// リザルト
	deathCount_ = 0;
	resultTextureHandle_[0] = TextureManager::Load("result/gameclear_bg.png");
	resultTextureHandle_[1] = TextureManager::Load("result/gameclear.png");
	resultTextureHandle_[2] = TextureManager::Load("result/gameover_bg.png");
	resultTextureHandle_[3] = TextureManager::Load("result/gameover.png");
	result_[0] = Sprite::Create(resultTextureHandle_[0], Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	result_[1] = Sprite::Create(resultTextureHandle_[1], Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	result_[2] = Sprite::Create(resultTextureHandle_[2], Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	result_[3] = Sprite::Create(resultTextureHandle_[3], Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	theta2 = 0.0f;
	resultPosition_ = Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f);

	// 3Dモデルデータの生成
	model_ = Model::Create();
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	modelBullet_ = Model::CreateFromOBJ("bullet", true);
	modelEnemy_ = Model::CreateFromOBJ("enemy", true);
	modelEnemyBullet_ = Model::CreateFromOBJ("enemybullet", true);
	modelSkydome_ = Model::CreateFromOBJ("aurora", true);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// レールカメラの初期化
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize();

	// 天球の初期化
	skyDome_ = std::make_unique<Skydome>();
	skyDome_->Initialize(modelSkydome_);

	// 自キャラの初期化
	player_ = std::make_unique<Player>();
	player_->SetParent(&railCamera_->GetWorldTransform());
	player_->Initialize(modelPlayer_, modelBullet_, textureHandle_);

	// 敵発生データの読み込み
	LoadEnemyPopData();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// 衝突マネージャの生成
	colliderManager_ = new ColliderManager();

	frame = 0;
}

void GameScene::Update(GameScene* gameScene) {

	if (!audio_->IsPlaying(bgm_)) {
		audio_->PlayWave(bgm_, true, 0.1f);
	}

	switch (scene) {
	case GameScene::Title:

		theta += 0.03f;
		titlePosition_.y = (float)WinApp::kWindowHeight / 2.0f - 15.0f + 20.0f * std::sinf(theta);
		title_[1]->SetPosition(titlePosition_);

		if (input_->TriggerKey(DIK_SPACE)) {
			player_.reset();
			for (std::list<std::unique_ptr<Enemy>>::iterator it = enemy_.begin(); it != enemy_.end(); ++it) {
				if ((*it)) {
					(*it).reset();
				}
			}
			railCamera_.reset();

			deathCount_ = 0;
			frame = 0;
			// ビュープロジェクションの初期化

			railCamera_ = std::make_unique<RailCamera>();
			railCamera_->Initialize();
			player_ = std::make_unique<Player>();
			player_->SetParent(&railCamera_->GetWorldTransform());
			player_->Initialize(modelPlayer_, modelBullet_, textureHandle_);
			// バッファをクリアします。
			enemyPopCommands.str("");
			// 状態をクリアします。
			enemyPopCommands.clear(std::stringstream::goodbit);
			LoadEnemyPopData();
			scene = Ingame;
		}

		break;

	case GameScene::Ingame:

		frame++;

		if (frame >= 150) {
			// デスフラグの立った弾を削除
			bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
				if (bullet->IsDead()) {
					return true;
				}
				return false;
			});
			// デスフラグの立った敵を削除
			enemy_.remove_if([](std::unique_ptr<Enemy>& enemy) {
				if (enemy) {
					if (enemy->IsDead()) {
						return true;
					}
				}
				return false;
			});
		}


		// レールカメラの更新
		railCamera_->Update();

		// 天球の更新
		skyDome_->Update();

		// 自キャラの更新
		player_->Update(viewProjection_, &railCamera_->GetWorldTransform());

		// 敵キャラ
		UpdateEnemyPopCommands(gameScene);

		// 敵キャラの更新
		for (std::list<std::unique_ptr<Enemy>>::iterator it = enemy_.begin(); it != enemy_.end(); ++it) {
			if ((*it)) {
				(*it)->Update(&railCamera_->GetWorldTransform());
			}
		}

		// 弾更新
		for (std::list<std::unique_ptr<EnemyBullet>>::iterator bullet = bullets_.begin();
		     bullet != bullets_.end(); ++bullet) {
			(*bullet)->Update();
		}

		// 衝突判定と応答
		if (frame >= 150) {
			ChackAllCollisions();
		}

		// ビュープロジェクション行列の更新と転送
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

		for (std::list<std::unique_ptr<Enemy>>::iterator it = enemy_.begin(); it != enemy_.end(); ++it) {
			if ((*it)) {
				if ((*it)->IsDead()) {
					deathCount_++;
				}
			}

		}

		if (player_->IsDead()) {
			deathCount_--;
		}

		if (deathCount_ >= 1 || deathCount_ <= -1) {
			scene = Result;
		}

		break;

	case GameScene::Result:

		theta2 += 0.03f;
		resultPosition_.y = (float)WinApp::kWindowHeight / 2.0f - 15.0f + 20.0f * std::sinf(theta2);

		if (deathCount_ >= 1) {
			result_[1]->SetPosition(resultPosition_);
		} else {
			result_[3]->SetPosition(resultPosition_);
		}

		if (input_->TriggerKey(DIK_SPACE)) {
			scene = Title;
		}

		break;
	default:
		break;
	}


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
	
	switch (scene) {
	case GameScene::Title:
		break;
	case GameScene::Ingame:

			// 天球の描画
		skyDome_->Draw(viewProjection_);

		// 自キャラの描画
		player_->Draw(viewProjection_);

		// 敵キャラの描画
		for (std::list<std::unique_ptr<Enemy>>::iterator it = enemy_.begin(); it != enemy_.end();
		     ++it) {
			if ((*it)) {
				for (std::list<std::unique_ptr<EnemyBullet>>::iterator bullet = bullets_.begin();
				     bullet != bullets_.end(); ++bullet) {
					(*bullet)->Draw(viewProjection_);
				}
				(*it)->Draw(viewProjection_);
			}
		}

		break;
	case GameScene::Result:
		break;
	default:
		break;
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

	switch (scene) {
	case GameScene::Title:

		title_[0]->Draw();
		title_[1]->Draw();

		break;
	case GameScene::Ingame:

	
		s_ui_base_->Draw();

		if (input_->PushKey(DIK_LEFT)) {
			s_left->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			s_left->SetColor({1.0f, 1.0f, 1.0f, 0.3f});
		}
		if (input_->PushKey(DIK_RIGHT)) {
			s_right->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			s_right->SetColor({1.0f, 1.0f, 1.0f, 0.3f});
		}
		if (input_->PushKey(DIK_UP)) {
			s_up->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			s_up->SetColor({1.0f, 1.0f, 1.0f, 0.3f});
		}
		if (input_->PushKey(DIK_DOWN)) {
			s_down->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			s_down->SetColor({1.0f, 1.0f, 1.0f, 0.3f});
		}
		if (input_->PushKey(DIK_SPACE)) {
			s_space->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		} else {
			s_space->SetColor({1.0f, 1.0f, 1.0f, 0.3f});
		}

		s_left->Draw();
		s_right->Draw();
		s_up->Draw();
		s_down->Draw();
		s_space->Draw();

		player_->DrawUI();

		for (std::list<std::unique_ptr<Enemy>>::iterator it = enemy_.begin(); it != enemy_.end(); ++it) {
			if (*it) {
				(*it)->DrawUI();
			}
		}

		break;
	case GameScene::Result:

		if (deathCount_ >= 1) {
			result_[0]->Draw();
			result_[1]->Draw();
		} else {
			result_[2]->Draw();
			result_[3]->Draw();
		}

		break;
	default:
		break;
	}


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::ChackAllCollisions() {

	// 自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

	// コライダーの解放
	colliderManager_->ClearColliderList();

	// コライダーをリストに登録
	colliderManager_->GetCollider(player_.get());
	for (auto& playerbullet : playerBullets) {
		colliderManager_->GetCollider(playerbullet.get());
	}
	for (auto& enemy : enemy_) {
		if (enemy) {
			colliderManager_->GetCollider(enemy.get());
		}
	}
	for (auto& enemybullet : bullets_) {
		colliderManager_->GetCollider(enemybullet.get());
	}

	colliderManager_->AllCollisions();

}

void GameScene::MakeEnemy(const Vector3& position, GameScene* gameScene) {
	// 敵キャラの生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	// 敵キャラに自キャラのアドレスを渡す
	newEnemy->SetPlayer(player_.get());
	// 敵キャラの初期化
	newEnemy->Initialize(modelEnemy_, modelEnemyBullet_, position, {0.0f, 0.0f, 0.0f}, gameScene, &railCamera_->GetWorldTransform(), railCamera_.get(), enemytextureHandle_);
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

/*
void GameScene::DrawCatmullRomSpline() {
	
	// 線分で描画する用の頂点リスト
	std::vector<Vector3> pointDrawing;
	// 線分の数
	const size_t segmentCount = 20;
	// スプライン曲線の制御点分回す
	if (controlPoints_.size() >= 4) {

		for (size_t i = 0; i < controlPoints_.size(); i++) {

			// 線分の数+1個分の頂点座標を計算
			for (size_t j = 0; j < segmentCount + 1; j++) {
				float t = 1.0f / segmentCount * j;
				Vector3 pos;

				if (i > 0 && i < controlPoints_.size() - 2) {
					pos = Vector3::CatmullRom(controlPoints_[i - 1], controlPoints_[i], controlPoints_[i + 1], controlPoints_[i + 2], t);
				} 
				else if (i == 0) {
					pos = Vector3::CatmullRom(controlPoints_[i], controlPoints_[i], controlPoints_[i + 1], controlPoints_[i + 2], t);
				} 
				else if (i < controlPoints_.size() - 1) {
					pos = Vector3::CatmullRom(controlPoints_[i - 1], controlPoints_[i], controlPoints_[i + 1], controlPoints_[i + 1], t);
				}
				// 描画用頂点リストに追加
				pointDrawing.push_back(pos);
			}
		}
	}

	primitiveDrawer_->SetViewProjection(&viewProjection_);
	for (size_t i = 0; i < pointDrawing.size() - 1; i++) {
		primitiveDrawer_->DrawLine3d(pointDrawing[i], pointDrawing[i + 1], {1.0f, 1.0f, 1.0f, 1.0f});
	}
	
}
*/
