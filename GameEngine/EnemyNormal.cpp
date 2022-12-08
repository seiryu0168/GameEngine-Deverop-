#include "EnemyNormal.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
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
	hModel_ = Model::Load("Assets\\Enemy2.fbx");
	pPlayer_ = (Player*)FindObject("Player"); //�m�F�p�I�u�W�F�N�g
	OBBCollider* pCollider = new OBBCollider(XMFLOAT3(1,1,1),false,false);
	AddCollider(pCollider);
	Model::SetModelNum(hModel_);

	transform_.position_.x = std::rand() % 100;
	transform_.position_.y = std::rand() % 100;
	transform_.position_.z = std::rand() % 100;
}

//�X�V
void EnemyNormal::Update()
{
	GetPositionVec() =XMLoadFloat3(&transform_.position_);    //���̍��W��vPosition�ɓ����
	
	////////////////�G�l�~�[�̏���/////////////
	XMFLOAT3 aa = GetPlayerPointer()->GetPosition();		//�v���C���[�̍��W�擾
	SetToPlayerVec(XMLoadFloat3(&aa) - GetPositionVec());	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����쐬

	if (IsVisible(frontVec_,0.5,50.0f))
	{
		EnemyMove();

	}
}

void EnemyNormal::FixedUpdate()
{

}

//�`��
void EnemyNormal::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void EnemyNormal::EnemyMove()
{
	SetPositionVec(XMLoadFloat3(&transform_.position_));//vPosition�ɍ��̍��W������
	XMVECTOR toTargetVec = XMLoadFloat3(&GetPlayerPointer()->GetPosition());
	XMVECTOR toVec = toTargetVec - GetPositionVec();
	toVec = XMVector3Normalize(toVec);							//�����̐��K��
	float angle = XMVectorGetX(XMVector3Dot(GetFrontVec(), toVec)); //�p�x�v�Z(���W�A��)
	transform_.rotate_.y = 1-angle;
	SetMatrixY(XMMatrixRotationY(transform_.rotate_.y));			//�p�x����]�s��ɕϊ�
	frontVec_ = XMVector3TransformCoord(toVec, matY_);			//�O�����x�N�g������]
	vPosition_ += toVec*0.3f;
	XMStoreFloat3(&transform_.position_, vPosition_);
}

//bool EnemyNormal::IsVisible(XMVECTOR vFront, float visibleAngle,float range)
//{
//
//	XMVECTOR toPlayer;
//	float rangeToPlayer;
//	rangeToPlayer = XMVectorGetX(XMVector3Length(toPlayerVec_));			//���E����p�̎��E�̒����擾
//	toPlayer = XMVector3Normalize(toPlayerVec_);							//���K��
//
//	XMVECTOR dot = XMVector3Dot(vFront, toPlayerVec_);						//���ς��v�Z
//	float angle = acos(min(XMVectorGetX(dot),1));						//�p�x�v�Z(1�ȏ�ɂȂ�Ȃ��悤min�֐�����)
//	if (rangeToPlayer <= 2 * range)
//	{
//		pPlayer_->AddTargetList(this);
//		isTargetList_ = true;
//		if (angle<visibleAngle && angle>-visibleAngle && rangeToPlayer < range)
//		{
//			return true;
//		}
//	}
//	else
//	{
//		isTargetList_ = false;
//	}
//
//	return false;
//}
void EnemyNormal::Attack()
{

}

void EnemyNormal::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		if (pPlayer_->GetSatatus() & ATC_ATTACK)
		{
			life_--;
			pPlayer_->SetStatus(ATC_DEFAULT);
			if (life_ < 0)
			{
				Transform pos;
				pos.position_= { 9999,9999,9999 };
				Model::SetTransform(hModel_,pos);
				KillMe();
			}
		}
	}
}

//�J��
void EnemyNormal::Release()
{
}