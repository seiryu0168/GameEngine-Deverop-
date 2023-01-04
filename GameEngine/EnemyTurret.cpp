#include "EnemyTurret.h"
#include"Engine/Model.h"
#include"Bullet.h"
#include"HomingBullet.h"
#include"Pointer.h"
#include"Engine/OBBCollider.h"
//�R���X�g���N�^
EnemyTurret::EnemyTurret(GameObject* parent)
	:Enemy(parent,"EnemyTurret"),
	hModel_(-1),
	shotTime_(0),
	rpm_(300)

{

}

//�f�X�g���N�^
EnemyTurret::~EnemyTurret()
{

}

//������
void EnemyTurret::Initialize()
{
	SetTag("Enemy");
	OBBCollider* pCollider = new OBBCollider(XMFLOAT3(1, 1, 1), false, false);
	AddCollider(pCollider);
	hModel_ = ModelManager::Load("Assets\\Enemy2.fbx");
	assert(hModel_ >= 0);
	ModelManager::SetModelNum(hModel_);
	
	XMFLOAT3 initPos = transform_.position_;
	initPos.x = rand() % 100;
	initPos.z = rand() % 100;
	RayCastData ray;
	ray.start = { initPos.x, 999.0f, initPos.z };
	ray.dir = { 0,1,0 };
	ModelManager::RayCast(hModel_, ray);
	if (ray.hit)
	{
		initPos.y = 999 - ray.dist;
	}
	transform_.position_ = initPos;
	SetPlayerPointer((Player*)FindObject("Player"));
}

//�X�V
void EnemyTurret::Update()
{
	SetPositionVec(XMLoadFloat3(&transform_.position_));
	GetEnemyState()->Update(this);
}

void EnemyTurret::Attack()
{
	Shot();
}

void EnemyTurret::Shot()
{
	
	shotTime_++;
	
	//shotTime��rpm_���g���Čv�Z�����l�ȏ�ɂȂ�����
	if ((3600.0f/(float)rpm_)<=(float)shotTime_)
	{
		XMVECTOR shotDir = XMVector3Normalize(GetToPlayerVec());
		Bullet* pBullet = Instantiate<Bullet>(this);
		pBullet->SetDir(shotDir);
		shotTime_ = 0;
	}

}

void EnemyTurret::FixedUpdate()
{

}
//�`��
void EnemyTurret::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void EnemyTurret::Release()
{

}

void EnemyTurret::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		if (GetPlayerPointer()->GetSatatus() & ATC_ATTACK)
		{
			DecreaseLife(1);
			GetPlayerPointer()->SetStatus(ATC_DEFAULT);
			if (GetLife() <= 0)
			{
				Transform pos;
				pos.position_ = { 9999,9999,9999 };
				ModelManager::SetTransform(hModel_, pos);
				KillMe();
			}
		}
	}
}
