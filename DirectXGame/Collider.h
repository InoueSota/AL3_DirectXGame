#pragma once

#include "WorldTransform.h"

/// <summary>
/// 衝突判定オブジェクト
/// </summary>
class Collider {
public:

	virtual ~Collider() {};

	/// <summary>
	/// 座標を取得
	/// </summary>
	virtual const Vector3& GetWorldPosition() const { return worldTransform_.translation_; }
	
	/// <summary>
	/// 半径を取得
	/// </summary>
	float GetRadius() { return radius_; }

	/// <summary>
	/// 半径を設定
	/// </summary>
	void SetRadius(float radius) { radius_ = radius; }
	
	/// <summary>
	/// 衝突時に呼ばれる関数
	/// </summary>
	virtual void OnCollision() = 0;


private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// 衝突半径
	float radius_ = 2.0f;
};

