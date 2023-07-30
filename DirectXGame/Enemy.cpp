#include "Enemy.h"
#include "EnemyBullet.h"
#include <cassert>
#include "BaseEnemyState.h"
#include "Player.h"
#include "GameScene.h"
#include "CollisionConfig.h"


Enemy::Enemy() {
	
	// 行動遷移
	state_ = new EnemyStateApproach();

	for (size_t i = 0; i < 9; i++) {
		delete red[i];
	}

}
Enemy::~Enemy() {
	
	// 行動遷移の解放
	delete state_;
}

void Enemy::Initialize(Model* model, Model* bulletModel, const Vector3& position, const Vector3& velocity, GameScene* gameScene, const WorldTransform* parent, RailCamera* railCamera, uint32_t textureHandle[4]) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	bulletModel_ = bulletModel; 

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("enemy/enemy.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

	// ゲームシーンのポインタを共有
	SetGameScene(gameScene);

	// レールカメラに追従させる
	SetParent(parent);
	railCamera_ = railCamera;

	frame = 0;
	isStart = false;
	hp = 100;
	Various::Srand();

	targetPosition_[0] = Vector3(-28.0f, 15.0f, 50.0f);
	targetPosition_[1] = Vector3(-10.0f, 15.0f, 50.0f);
	targetPosition_[2] = Vector3(8.0f, 15.0f, 50.0f);
	targetPosition_[3] = Vector3(-28.0f, 0.0f, 50.0f);
	targetPosition_[4] = Vector3(-10.0f, 0.0f, 50.0f);
	targetPosition_[5] = Vector3(8.0f, 0.0f, 50.0f);
	targetPosition_[6] = Vector3(-28.0f, -15.0f, 50.0f);
	targetPosition_[7] = Vector3(-10.0f, -15.0f, 50.0f);
	targetPosition_[8] = Vector3(8.0f, -15.0f, 50.0f);

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributeEnemy);
	// 衝突対象を自分の属性以外に設定
	SetCollisionMask(~kCollisionAttributeEnemy);

	for (size_t i = 0; i < 9; i++) {
		red[i] = Sprite::Create(textureHandle[i], Vector2((float)WinApp::kWindowWidth / 2.0f, (float)WinApp::kWindowHeight / 2.0f), {1, 1, 1, 1}, {0.5f, 0.5f});
	}


}

void Enemy::Update(const WorldTransform* parent) {
	
	if (hp <= 0) {
		isDead_ = true;
	}


	if (hp <= 75) {
		if (interval_ < 120) {
			beforeFire_ = 0;
			isStart = false;
			interval_++;
		}
		if (interval_ >= 120) {

			if (!isStart) {
				bullet_1 = Various::Random(0, 8);
				bullet_2 = Various::Random(0, 8);
				bullet_3 = Various::Random(0, 8);

				while (bullet_1 == bullet_2) {
					bullet_2 = Various::Random(0, 8);
				}
				while (bullet_1 == bullet_3 || bullet_2 == bullet_3) {
					bullet_3 = Various::Random(0, 8);
				}
				isStart = true;
			}

			bulletTarget_[0] = targetPosition_[bullet_1];
			bulletTarget_[1] = targetPosition_[bullet_2];
			bulletTarget_[2] = targetPosition_[bullet_3];
			beforeFire_++;

			if (beforeFire_ >= 120) {
				Fire(parent, bulletTarget_[0]);
				Fire(parent, bulletTarget_[1]);
				Fire(parent, bulletTarget_[2]);
				interval_ = 0;
			}
		}
	} else if (hp <= 150) {
		if (interval_ < 120) {
			beforeFire_ = 0;
			isStart = false;
			interval_++;
		}
		if (interval_ >= 120) {

			if (!isStart) {
				bullet_1 = Various::Random(0, 8);
				bullet_2 = Various::Random(0, 8);

				while (bullet_1 == bullet_2) {
					bullet_2 = Various::Random(0, 8);
				}

				isStart = true;
			}

			bulletTarget_[0] = targetPosition_[bullet_1];
			bulletTarget_[1] = targetPosition_[bullet_2];
			beforeFire_++;

			if (beforeFire_ >= 120) {
				Fire(parent, bulletTarget_[0]);
				Fire(parent, bulletTarget_[1]);
				interval_ = 0;
			}
		}
	} else {
		
		if (interval_ < 120) {
			beforeFire_ = 0;
			isStart = false;
			interval_++;
		}
		if (interval_ >= 120){

			if (!isStart) {
				bullet_1 = Various::Random(0, 8);
				isStart = true;
			}

			bulletTarget_[0] = targetPosition_[bullet_1];
			beforeFire_++;

			if (beforeFire_ >= 120) {
				Fire(parent, bulletTarget_[0]);
				interval_ = 0;
			}
		}

	}

	state_->Update(this);

	// WorldTransformの更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::DrawUI() 
{
	if (interval_ >= 120) {

		if (hp <= 75) {
			red[bullet_1]->Draw();
			red[bullet_2]->Draw();
			red[bullet_3]->Draw();

		} else if (hp <= 150) {
			red[bullet_1]->Draw();
			red[bullet_2]->Draw();

		} else {
			red[bullet_1]->Draw();
		}
	}
}

void Enemy::ChangeState(BaseEnemyState* newState) {

	// 状態遷移
	delete state_;
	state_ = newState;

	// 遷移した
	isChangeState_ = true;
}

void Enemy::Move(const Vector3& vector) {

	// 受け取った引数分、敵を動かす
	worldTransform_.translation_ += vector;
}

void Enemy::Fire(const WorldTransform* parent, Vector3& bulletTarget) {

	assert(player_);

	// 弾を生成し、初期化
	std::unique_ptr<EnemyBullet>newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(bulletModel_, worldTransform_.translation_, parent, bulletTarget);

	// 弾を登録する
	gameScene_->AddEnemyBullet(std::move(newBullet));
}

// 親となるWorldTransformをセット
void Enemy::SetParent(const WorldTransform* parent) {

	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;

}