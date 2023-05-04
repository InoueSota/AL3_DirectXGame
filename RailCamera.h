#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:
	RailCamera();
	~RailCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position, const float radian);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ViewPrpjectionを取得する
	/// </summary>
	const ViewProjection& GetViewProjection() const { return viewProjection_; }

	/// <summary>
	/// WorldMatrixを取得する
	/// </summary>
	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

private:

	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

};

