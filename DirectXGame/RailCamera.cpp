#include "RailCamera.h"
#include "ImGuiManager.h"
#include "Matrix4x4.h"

RailCamera::RailCamera() {}
RailCamera::~RailCamera() {}

// 初期化
void RailCamera::Initialize() {

	worldTransform_.scale_.x = 1.0f;
	worldTransform_.scale_.y = 1.0f;
	worldTransform_.scale_.z = 1.0f;
	// ViewProjectionの初期化
	viewProjection_.Initialize();

	controlPoints_ = {
		{  5,  0, 20 },
		{  2,  2, 15 },
		{  5,  4, 10 },
		{  8,  6,  5 },
		{  5,  4,  0 },
		{  5,  2,  5 },
		{  8,  0, 10 },
		{  5,  2, 15 },
		{  2,  0, 20 }
	};

	// スプライン曲線の制御点分回す
	if (controlPoints_.size() >= 4) {

		for (size_t i = 0; i < controlPoints_.size(); i++) {

			float partCount = 0.0f;
			if (i != controlPoints_.size() - 1) {
				float length = Vector3::Length(controlPoints_[i + 1] - controlPoints_[i]);
				partCount = 50.0f * length;
			} else {
				float length = Vector3::Length(controlPoints_[0] - controlPoints_[i]);
				partCount = 50.0f * length;
			}

			// 線分の数+1個分の頂点座標を計算
			for (size_t j = 0; j < partCount; j++) {
				float t = 1.0f / partCount * j;
				Vector3 pos;

				if (i > 0 && i < controlPoints_.size() - 2) {
					pos = Vector3::CatmullRom(controlPoints_[i - 1], controlPoints_[i], controlPoints_[i + 1], controlPoints_[i + 2], t);
				} else if (i == 0) {
					pos = Vector3::CatmullRom(controlPoints_[controlPoints_.size() - 1], controlPoints_[0], controlPoints_[1], controlPoints_[2], t);
				} else if (i == controlPoints_.size() - 2) {
					pos = Vector3::CatmullRom(controlPoints_[controlPoints_.size() - 3], controlPoints_[controlPoints_.size() - 2], controlPoints_[controlPoints_.size() - 1], controlPoints_[0], t);
				} else if (i == controlPoints_.size() - 1) {
					pos = Vector3::CatmullRom(controlPoints_[controlPoints_.size() - 2], controlPoints_[controlPoints_.size() - 1], controlPoints_[0], controlPoints_[1], t);
				}
				catmullRomPoints_.push_back(pos);
			}
		}
	}

	deltaEye = 0;
	deltaTarget = 1;
}

// 更新
void RailCamera::Update() {

	// 配列外にいきそうなときに初期化する
	if (deltaTarget == catmullRomPoints_.size()) {
		deltaTarget = 0;
	}
	if (deltaEye == catmullRomPoints_.size()) {
		deltaEye = 0;
	}

	// 視点と注視点
	Vector3 eye = catmullRomPoints_[deltaEye];
	Vector3 target = catmullRomPoints_[deltaTarget];
	deltaEye++;
	deltaTarget++;

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Matrix4x4::Inverse(worldTransform_.matWorld_);
	// ビュープロジェクションを転送
	viewProjection_.TransferMatrix();

	// 前方ベクトル
	Vector3 forward = target - eye;

	worldTransform_.translation_ = eye;
	worldTransform_.rotation_.y = std::atan2(forward.x, forward.z);
	float velocityXZ = std::sqrt(forward.x * forward.x + forward.z * forward.z);
	worldTransform_.rotation_.x = std::atan2(-forward.y, velocityXZ);

	// WorldTransformのワールド行列再計算
	worldTransform_.matWorld_ = Matrix4x4::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

}