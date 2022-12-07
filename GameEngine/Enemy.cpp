#include "Enemy.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent,std::string name)
	:GameObject(parent,name),
	life_(5),
	toPlayerVec_(XMVectorSet(0, 0, 0, 0)),
	frontVec_(XMVectorSet(0, 0, 1, 0)),
	upVec_(XMVectorSet(0, 1, 0, 0)),
	matX_(XMMatrixIdentity()),
	matY_(XMMatrixIdentity()),
	visibleFlag_(false),
	isTargetList_(false),
	vPosition_(XMVectorSet(0, 0, 0, 0)),
	pPlayer_(nullptr)
{

}

//�f�X�g���N�^
Enemy::~Enemy()
{

}


bool Enemy::IsVisible(XMVECTOR vFront, float visibleAngle, float range)
{

	XMVECTOR toPlayer;
	float rangeToPlayer;
	rangeToPlayer = XMVectorGetX(XMVector3Length(toPlayerVec_));			//���E����p�̎��E�̒����擾
	toPlayer = XMVector3Normalize(toPlayerVec_);							//���K��

	XMVECTOR dot = XMVector3Dot(vFront, toPlayerVec_);						//���ς��v�Z
	float angle = acos(min(XMVectorGetX(dot), 1));						//�p�x�v�Z(1�ȏ�ɂȂ�Ȃ��悤min�֐�����)
	if (rangeToPlayer <= 2 * range)
	{
		pPlayer_->AddTargetList(this);
		isTargetList_ = true;
		if (angle<visibleAngle && angle>-visibleAngle && rangeToPlayer < range)
		{
			return true;
		}
	}
	else
	{
		isTargetList_ = false;
	}

	return false;
}
void Enemy::ChangeState(EnemyState* state)
{
	pEnemyState_ = state;
	pEnemyState_->Init(this);
}