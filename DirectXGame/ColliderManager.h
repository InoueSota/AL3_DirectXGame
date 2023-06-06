#pragma once
#include <list>
#include "Collider.h"

class ColliderManager {
public:
	ColliderManager() {};

	/// <summary>
	/// コライダーを引数で受け取り、コライダーリストに登録する関数
	/// </summary>
	void GetCollider(Collider* collider) { colliders_.push_back(collider); }

	/// <summary>
	/// コライダーリストをクリアする関数
	/// </summary>
	void ClearColliderList() { colliders_.clear(); }

	/// <summary>
	/// コライダー2つの衝突判定と応用
	/// </summary>
	/// <param name="colliderA">コライダーA</param>
	/// <param name="colliderB">コライダーB</param>
	void AllCollisions();

	/// <summary>
	/// コライダー2つの衝突判定と応用
	/// </summary>
	/// <param name="colliderA">コライダーA</param>
	/// <param name="colliderB">コライダーB</param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

private:
	// コライダーリスト
	std::list<Collider*> colliders_;
};

