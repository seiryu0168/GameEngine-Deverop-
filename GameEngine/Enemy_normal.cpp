#include "Enemy_normal.h"
#include"Engine/Model.h"
#include"Pointer.h"
//�R���X�g���N�^
Enemy_normal::Enemy_normal(GameObject* parent)
	:Enemy(parent, "Enemy_normal"),
	hModel_(-1),
	frontVec_(XMVectorSet(0, 0, 1, 0)),
	upVec_(XMVectorSet(0,1,0,0)),
	matX_(XMMatrixIdentity()),
	matY_(XMMatrixIdentity()),
	visibleFlag_(false),
	vPosition_(XMVectorSet(0,0,0,0)),
	pPlayer_(nullptr)
{

}

//�f�X�g���N�^
Enemy_normal::~Enemy_normal()
{
	Release();
}

//������
void Enemy_normal::Initialize()
{
	hModel_ = Model::Load("Assets\\TestBox.fbx");
	pPlayer_ = (Player*)FindObject("Player"); //�m�F�p�I�u�W�F�N�g
	Instantiate<Pointer>(this);
}

//�X�V
void Enemy_normal::Update()
{
	vPosition_ =XMLoadFloat3(&transform_.position_);    //���̍��W��vPosition�ɓ����


	////////////////�m�F�p�I�u�W�F�N�g�\��////////////
	Pointer* pPointer = (Pointer*)FindChild("Pointer");
	XMFLOAT3 po;
	XMStoreFloat3(&po, vPosition_+frontVec_);
	pPointer->SetPointerPos(po);
	pPointer->SetDraw(true);
	
	////////////////�G�l�~�[�̏���/////////////
	XMVECTOR toPlayer;
	XMFLOAT3 aa = pPlayer_->GetPosition();		//�v���C���[�̍��W�擾
	toPlayer = XMLoadFloat3(&aa) - vPosition_;	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����쐬

	if (IsVisible(frontVec_,XMLoadFloat3(&aa),0.5,50.0f)/*&&visibleFlag_*/)
	{
		EnemyMove(toPlayer);
	}
}

void Enemy_normal::FixedUpdate()
{

}
//�`��
void Enemy_normal::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy_normal::EnemyMove(XMVECTOR toVec)
{
	
	vPosition_ = XMLoadFloat3(&transform_.position_);			//vPosition�ɍ��̍��W������
	toVec = XMVector3Normalize(toVec);							//�����̐��K��
	float angle = XMVectorGetX(XMVector3Dot(frontVec_, toVec)); //�p�x�v�Z(���W�A��)
	matY_ = XMMatrixRotationY(1-angle);							//�p�x����]�s��ɕϊ�
	frontVec_ = XMVector3TransformCoord(toVec, matY_);			//�O�����x�N�g������]
	
	vPosition_ += toVec*0.3f;
	XMStoreFloat3(&transform_.position_, vPosition_);
}

bool Enemy_normal::IsVisible(XMVECTOR vFront, XMVECTOR vTarget, float visibleAngle,float range)
{
	vFront = XMVector3Normalize(vFront);								//���K��
	XMVECTOR toVector = vTarget - XMLoadFloat3(&transform_.position_);	//�ڕW�Ɍ������x�N�g��
	float rangeToPlayer;
	rangeToPlayer = XMVectorGetX(XMVector3Length(toVector));			//���E����p�̎��E�̒����擾
	toVector = XMVector3Normalize(toVector);							//���K��

	XMVECTOR dot = XMVector3Dot(vFront, toVector);						//���ς��v�Z
	float angle = acos(min(XMVectorGetX(dot),1));						//�p�x�v�Z(1�ȏ�ɂȂ�Ȃ��悤min�֐�����)


	if (angle<visibleAngle && angle>-visibleAngle&&rangeToPlayer<range)
	{
		return true;
	}

	return false;
}

//�J��
void Enemy_normal::Release()
{
}