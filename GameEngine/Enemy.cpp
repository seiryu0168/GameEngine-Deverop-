#include "Enemy.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent, std::string name)
	:GameObject(parent, name)
{
	
	enemyParameter_.life = 5;
	enemyParameter_.toPlayerVec = XMVectorSet(0, 0, 0, 0);
	enemyParameter_.frontVec = XMVectorSet(0, 0, 1, 0);
	enemyParameter_.upVec = XMVectorSet(0, 1, 0, 0);
	enemyParameter_.matX = XMMatrixIdentity();
	enemyParameter_.matY; XMMatrixIdentity();
	enemyParameter_.visibleFlag = false;
	enemyParameter_.isTargetList = false;
	enemyParameter_.vPosition = XMVectorSet(0, 0, 0, 0);
	enemyParameter_.pPlayer = nullptr;

}

//�f�X�g���N�^
Enemy::~Enemy()
{

}


bool Enemy::IsVisible(XMVECTOR vFront, float visibleAngle, float range)
{

	XMVECTOR toPlayer;
	float rangeToPlayer;
	rangeToPlayer = XMVectorGetX(XMVector3Length(enemyParameter_.toPlayerVec));			//���E����p�̎��E�̒����擾
	toPlayer = XMVector3Normalize(enemyParameter_.toPlayerVec);							//���K��

	XMVECTOR dot = XMVector3Dot(vFront, enemyParameter_.toPlayerVec);						//���ς��v�Z
	float angle = acos(min(XMVectorGetX(dot), 1));						//�p�x�v�Z(1�ȏ�ɂȂ�Ȃ��悤min�֐�����)
	if (rangeToPlayer <= 2 * range)
	{
		enemyParameter_.pPlayer->AddTargetList(this);
		enemyParameter_.isTargetList = true;
		if (angle<visibleAngle && angle>-visibleAngle && rangeToPlayer < range)
		{
			return true;
		}
	}
	else
	{
		enemyParameter_.isTargetList = false;
	}

	return false;
}
void Enemy::ChangeState(EnemyState* state)
{
	pEnemyState_ = state;
	pEnemyState_->Init(this);
}