#include "EnemyStateDef.h"
#include"EnemyNormal.h"
#include"StateList.h"

//�X�e�[�^�X���`����N���X


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
	{//�G�l�~�[���v���C���[����������X�e�[�^�X��ς���

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
	//�U��
	enemy->Attack();
	if (!(enemy->IsVisible(enemy->GetViewAngle(), enemy->GetViewRange())))
	{

		enemy->ChangeState(State::search->GetInstance());

	}
}