#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include <vector>

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
	void Initialize();

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

	// スプライン曲線制御点（通過点）
	std::vector<Vector3> controlPoints_;
	std::vector<Vector3> catmullRomPoints_;

	int deltaEye;
	int deltaTarget;

};

