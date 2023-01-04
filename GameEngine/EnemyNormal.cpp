#include "EnemyNormal.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
#include"StateList.h"
#include"Pointer.h"
//�R���X�g���N�^
EnemyNormal::EnemyNormal(GameObject* parent)
	:Enemy(parent, "EnemyNormal"),
	hModel_(-1)
{

}

//�f�X�g���N�^
EnemyNormal::~EnemyNormal()
{
	Release();
}

//������
void EnemyNormal::Initialize()
{
	SetTag("Enemy");
	hModel_ = ModelManager::Load("Assets\\Enemy2.fbx");
	OBBCollider* pCollider = new OBBCollider(XMFLOAT3(1,1,1),false,false);
	AddCollider(pCollider);
	ModelManager::SetModelNum(hModel_);

	transform_.position_.x = std::rand() % 100;
	transform_.position_.y = std::rand() % 100;
	transform_.position_.z = std::rand() % 100;
	SetPlayerPointer((Player*)FindObject("Player"));
}

//�X�V
void EnemyNormal::Update()
{
	SetPositionVec(XMLoadFloat3(&transform_.position_));
	GetEnemyState()->Update(this);
}

void EnemyNormal::FixedUpdate()
{

}

//�`��
void EnemyNormal::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void EnemyNormal::EnemyMove()
{
	SetPositionVec(XMLoadFloat3(&transform_.position_));//vPosition�ɍ��̍��W������
	XMFLOAT3 playerPos = GetPlayerPointer()->GetPosition();
	XMVECTOR toTargetVec = XMLoadFloat3(&playerPos);
	XMVECTOR toVec = toTargetVec - GetPositionVec();
	toVec = XMVector3Normalize(toVec);							//�����̐��K��
	float angle = XMVectorGetX(XMVector3Dot(GetFrontVec(), toVec)); //�p�x�v�Z(���W�A��)
	transform_.rotate_.y = 1-angle;
	SetMatrixY(XMMatrixRotationY(transform_.rotate_.y));			//�p�x����]�s��ɕϊ�
	SetFrontVec(XMVector3TransformCoord(toVec, GetMatrixY()));			//�O�����x�N�g������]
	toVec *= 0.6f;
	toVec += GetPositionVec();
	SetPositionVec(toVec);
	XMStoreFloat3(&transform_.position_, toVec);
}

void EnemyNormal::Attack()
{
	EnemyMove();
}

void EnemyNormal::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		if (GetPlayerPointer()->GetSatatus() & ATC_ATTACK)
		{
			DecreaseLife(1);
			GetPlayerPointer()->SetStatus(ATC_DEFAULT);
			if (GetLife() < 0)
			{
				Transform pos;
				pos.position_= { 9999,9999,9999 };
				ModelManager::SetTransform(hModel_,pos);
				KillMe();
			}
		}
	}
}

//�J��
void EnemyNormal::Release()
{
}