#include "BaseEnemyState.h"
#include "Enemy.h"



void EnemyStateApproach::Update(Enemy* pEnemy) {

	pEnemy->Move(velocity);
	if (pEnemy->GetEnemyPosition().z < 0.0f) {
		pEnemy->ChangeState(new EnemyStateLeave);
	}
}

void EnemyStateLeave::Update(Enemy* pEnemy) {

	pEnemy->Move(velocity);
}