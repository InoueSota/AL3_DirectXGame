#include "ColliderManager.h"

void ColliderManager::AllCollisions() {

	// リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {

		// イテレータBはイテレータAの次の要素から回す（重複判定を回避）
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {

			// ペアの当たり判定
			CheckCollisionPair((*itrA), (*itrB));
		}
	}
}

void ColliderManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	// 衝突フィルタリング
	if (!(colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) ||
	    !(colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask())) {
		return;
	}

	Vector3 positionA = colliderA->GetWorldPosition();
	Vector3 positionB = colliderB->GetWorldPosition();

	// 球と球の交差判定
	float direction =
	    (std::powf(positionA.x - positionB.x, 2.0f) + std::powf(positionA.y - positionB.y, 2.0f) +
	     std::powf(positionA.z - positionB.z, 2.0f));

	// 球と球の交差判定
	if (direction <= std::powf(colliderA->GetRadius() + colliderB->GetRadius(), 2.0f)) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}
