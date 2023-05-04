#include "Skydome.h"


Skydome::Skydome() {}
Skydome::~Skydome() {}

// 初期化
void Skydome::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);
	model_ = model;

	// 天球の座標
	worldTransform_.Initialize();
	worldTransform_.scale_.x = 800.0f;
	worldTransform_.scale_.y = 800.0f;
	worldTransform_.scale_.z = 800.0f;
}

// 更新
void Skydome::Update() {

	// WorldTransformの更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Skydome::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection);
}
