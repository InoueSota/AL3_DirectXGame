#include "Player.h"
#include "Matrix4x4.h"
#include "ImGuiManager.h"
#include "PlayerBullet.h"



Player::Player() {}
Player::~Player() {

	// 2Dレティクル解放
	delete sprite2DReticle_;
}

void Player::Initialize(Model* model, uint32_t textureHandle, uint32_t reticleTextureHandle) {

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f, 0.0f, 50.0f};

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();
	// スプライト生成
	sprite2DReticle_ = Sprite::Create(reticleTextureHandle, {0.0f, 0.0f}, {1,1,1,1},{0.5f,0.5f});
}

void Player::Update(const ViewProjection& viewProjection) {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		if (bullet->IsDead()) {
			return true;
		}
		return false;
	});

	// 旋回処理
	Rotate();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動（ベクトルの加算）
	worldTransform_.translation_ += move;

	// 移動限界座標
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// 攻撃処理
	Attack();

	// 弾更新
	for (std::list<std::unique_ptr<PlayerBullet>>::iterator it = bullets_.begin(); it != bullets_.end(); ++it) {
		(*it)->Update();
	}

	// ImGuiで値を入力する変数
	float tmpFloat3[3] = {worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z};
	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Player");
	ImGui::SliderFloat3("position", tmpFloat3, -50.0f, 50.0f);
	ImGui::End();

	// 入力された値をポジションに代入する
	worldTransform_.translation_.x = tmpFloat3[0];
	worldTransform_.translation_.y = tmpFloat3[1];
	worldTransform_.translation_.z = tmpFloat3[2];

	// 行列更新と転送
	worldTransform_.UpdateMatrix();

	// 自機のワールド座標から3Dレティクルのワールド座標を計算
	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 50.0f;
	// 自機から3Dレティクルへのオフセット（Z+向き）
	Vector3 offset = {0.0f, 0.0f, 1.0f};
	// 自機のワールド行列の回転を反映
	offset = Vector3::TransformNormal(offset, worldTransform_.matWorld_);
	// ベクトルの長さを整える
	offset = offset.Normalize() * kDistancePlayerTo3DReticle;
	// 3Dレティクルの座標を設定
	worldTransform3DReticle_.translation_ = offset + GetWorldPosition();
	worldTransform3DReticle_.UpdateMatrix();

	// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
	Vector3 positionReticle = worldTransform3DReticle_.matWorld_.GetTranslate();
	// ビューポート行列
	Matrix4x4 matViewport = Matrix4x4::MakeViewportMatrix(0,0,WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	//Matrix4x4 matViewProjectionViewport = viewProjection.matView * viewProjection.matProjection * matViewport;
	// ワールド→スクリーン座標変換（ここで3Dから2Dになる）
	viewProjection;
}

void Player::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);

	// 弾描画
	for (std::list<std::unique_ptr<PlayerBullet>>::iterator it = bullets_.begin(); it != bullets_.end(); ++it) {
		(*it)->Draw(viewProjection);
	}
}

void Player::DrawUI() {

	// 2Dレティクルを描画
	sprite2DReticle_->Draw();
}

void Player::Rotate() {
	
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		const float kBulletSpeed = 1.5f;
		Vector3 velocity = { worldTransform3DReticle_.matWorld_.GetTranslate() - worldTransform_.matWorld_.GetTranslate() };
		velocity = velocity.Normalize() * kBulletSpeed;

		// 速度ベクトルを目標の向きに合わせて回転させる
		velocity = Vector3::TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.matWorld_.GetTranslate(), velocity);

		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

// 親となるWorldTransformをセット
void Player::SetParent(const WorldTransform* parent) {

	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}