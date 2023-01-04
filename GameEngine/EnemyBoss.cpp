#include "EnemyBoss.h"
#include"Engine/Model.h"
#include"Bullet.h"
#include"HomingBullet.h"
namespace
{
	static const float nearRange = 75.0f;
	static const float farRange = 125.0f;
}
EnemyBoss::EnemyBoss(GameObject* parent)
	:Enemy(parent,"EnemyBoss"),
	rpm_(200)
{
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::Initialize()
{
	SetTag("Enemy");
	OBBCollider* pCollider = new OBBCollider(XMFLOAT3(1, 1, 1), false, false);
	AddCollider(pCollider);
	ModelManager::SetModelNum(hModel_);

	hModel_ = ModelManager::Load("Assets\\EnemyBoss.fbx");
	assert(hModel_ >= 0);
	SetPlayerPointer((Player*)FindObject("Player"));
	SetviewAngle(M_PI);
	SetviewRange(200);
	
	transform_.position_ = { 110,0,110 };
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
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void EnemyBoss::Attack()
{
	if (XMVectorGetX(XMVector3Length(GetToPlayerVec()))<nearRange)
	{
		//�U��1
		//���i����e�ōU��

		Shot();
	}
	else if(XMVectorGetX(XMVector3Length(GetToPlayerVec())) < farRange)
	{
		//�U��2
		//�ǔ��e�ōU��
		HShot();
	}
}

void EnemyBoss::HShot()
{
	shotTime_++;
	float isShot = 3600.0f / rpm_;
	if (isShot <= (float)shotTime_)
	{
		XMVECTOR shotDir = XMVector3Normalize(GetToPlayerVec());
		HomingBullet* pHBullet = Instantiate<HomingBullet>(this);
		shotTime_ = 0;
	}
}

void EnemyBoss::Shot()
{
	shotTime_++;
	float isShot = 3600.0f / rpm_;
	if (isShot <= (float)shotTime_)
	{
		XMVECTOR shotDir = XMVector3Normalize(GetToPlayerVec());
		Bullet* pBullet = Instantiate<Bullet>(this);
		pBullet->SetDir(shotDir);
		shotTime_ = 0;
	}
}

void EnemyBoss::Release()
{
}

void EnemyBoss::OnCollision(GameObject* pTarget)
{
}

