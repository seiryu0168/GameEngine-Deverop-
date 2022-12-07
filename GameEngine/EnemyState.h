#pragma once
class Enemy;
class EnemyState
{
public:
	virtual ~EnemyState() {};
	virtual void Init(Enemy* enemy)=0;
	virtual void Update(Enemy* enemy)=0;
};

