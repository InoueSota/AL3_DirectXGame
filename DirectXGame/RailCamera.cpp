#include "RailCamera.h"
#include "ImGuiManager.h"
#include "Matrix4x4.h"

RailCamera::RailCamera() {}
RailCamera::~RailCamera() {}

// 初期化
void RailCamera::Initialize(const Vector3& position, const float radian) {

	// WorldTransformの初期設定
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.x = radian;
	worldTransform_.rotation_.y = radian;
	worldTransform_.rotation_.z = radian;
	worldTransform_.scale_.x = 1.0f;
	worldTransform_.scale_.y = 1.0f;
	worldTransform_.scale_.z = 1.0f;
	// ViewProjectionの初期化
	viewProjection_.Initialize();
}

// 更新
void RailCamera::Update() {

	// WorldTransformの座標の数値を加算したりする（移動）
	//worldTransform_.translation_.z += 0.1f;
	
	// WorldTransformの角度の数値を加算したりする（回転）

	// WorldTransformのワールド行列再計算
	worldTransform_.matWorld_ = Matrix4x4::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Matrix4x4::Inverse(worldTransform_.matWorld_);
	// ビュープロジェクションを転送
	viewProjection_.TransferMatrix();

	// カメラの座標を画面表示する処理
	float tmpTransfrom3[3] = {worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z};
	float tmpRotation3[3] = {worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", tmpTransfrom3, -1000.0f, 1000.0f);
	ImGui::SliderFloat3("rotation", tmpRotation3, -10.0f, 10.0f);
	ImGui::End();

	// 入力された値をポジションに代入する
	worldTransform_.translation_ = {tmpTransfrom3[0], tmpTransfrom3[1], tmpTransfrom3[2]};
	worldTransform_.rotation_ = {tmpRotation3[0], tmpRotation3[1], tmpRotation3[2]};
}