#include "EnemyBoss.h"
#include"Engine/Model.h"

EnemyBoss::EnemyBoss(GameObject* parent)
	:Enemy(parent,"EnemyBoss")
{
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::Initialize()
{
	OBBCollider* pCollider = new OBBCollider(XMFLOAT3(1, 1, 1), false, false);
	AddCollider(pCollider);
	ModelManager::SetModelNum(hModel_);

	hModel_ = ModelManager::Load("Assets\\EnemyBoss.fbx");
	assert(hModel_ >= 0);
	SetPlayerPointer((Player*)FindObject("Player"));

}

void EnemyBoss::Update()
{
	SetPositionVec(XMLoadFloat3(&transform_.position_));
	GetEnemyState()->Update(this);
}

void EnemyBoss::FixedUpdate()
{
}

void EnemyBoss::Draw()
{
}

void EnemyBoss::Attack()
{
	if (XMVectorGetX(XMVector3Length(GetToPlayerVec()))<50)
	{
		//�U��1
		//���a50�ȓ��ɔ͈͍U��
		//����������o�Ă���

	}
	else
	{
		//�U��2
		//�ǔ��e�ōU��
	}
}

void EnemyBoss::Release()
{
}

void EnemyBoss::OnCollision(GameObject* pTarget)
{
}
