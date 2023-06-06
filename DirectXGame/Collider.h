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

	/// <summary>
	/// 衝突属性（自分）を取得
	/// </summary>
	const uint32_t& GetCollisionAttribute() const { return collisionAttribute_; }
	/// <summary>
	/// 衝突属性（自分）を設定
	/// </summary>
	void SetCollisionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }
	/// <summary>
	/// 衝突マスク（相手）を取得
	/// </summary>
	const uint32_t& GetCollisionMask() const { return collisionMask_; }
	/// <summary>
	/// 衝突マスク（相手）を設定
	/// </summary>
	void SetCollisionMask(uint32_t collisionMask) { collisionMask_ = collisionMask; }


private:
	// 衝突属性（自分）
	uint32_t collisionAttribute_ = 0xffffffff;
	// 衝突マスク（相手）
	uint32_t collisionMask_ = 0xffffffff;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// 衝突半径
	float radius_ = 2.0f;
};

