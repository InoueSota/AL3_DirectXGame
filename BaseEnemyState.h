#pragma once
#include "Vector3.h"



class Enemy;

class BaseEnemyState {
public:
	virtual ~BaseEnemyState() {};

	// 純粋仮想関数
	virtual void Update(Enemy* pEnemy) = 0;
};

class EnemyStateApproach : public BaseEnemyState {
public:
	void Update(Enemy* pEnemy);

private:
	Vector3 velocity = { 0.0f, 0.0f, -0.0f };
};

class EnemyStateLeave : public BaseEnemyState {
public:
	void Update(Enemy* pEnemy);

private:
	Vector3 velocity = { -0.2f, 0.2f, 0.0f };
};