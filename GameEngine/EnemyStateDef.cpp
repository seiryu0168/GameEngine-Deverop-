#include "EnemyStateDef.h"
#include"EnemyNormal.h"
#include"StateList.h"

////////////////////////////////////////////���G���///////////////////////////////////////////
StateSearch::~StateSearch()
{

}

void StateSearch::Init(Enemy* enemy)
{
	
}
void StateSearch::Update(Enemy* enemy)
{
	if (enemy->IsVisible(enemy->GetViewAngle(), enemy->GetViewRange()))
	{

		enemy->ChangeState(State::chase->GetInstance());

	}
}

////////////////////////////////////////////�ǐՏ��//////////////////////////////////////////
StateChase::~StateChase()
{

}

void StateChase::Init(Enemy* enemy)
{

}
void StateChase::Update(Enemy* enemy)
{
	enemy->Attack();
	if (!(enemy->IsVisible(enemy->GetViewAngle(), enemy->GetViewRange())))
	{

		enemy->ChangeState(State::search->GetInstance());

	}
}