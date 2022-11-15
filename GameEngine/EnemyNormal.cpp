#include "EnemyNormal.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
#include"Pointer.h"
//�R���X�g���N�^
EnemyNormal::EnemyNormal(GameObject* parent)
	:Enemy(parent, "EnemyNormal"),
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
EnemyNormal::~EnemyNormal()
{
	Release();
}

//������
void EnemyNormal::Initialize()
{
	hModel_ = Model::Load("Assets\\TestBox.fbx");
	pPlayer_ = (Player*)FindObject("Player"); //�m�F�p�I�u�W�F�N�g
	BoxCollider* pCollider = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
	AddCollider(pCollider);
	Model::SetModelNum(hModel_);
	//Instantiate<Pointer>(this);
}

//�X�V
void EnemyNormal::Update()
{
	vPosition_ =XMLoadFloat3(&transform_.position_);    //���̍��W��vPosition�ɓ����

	////////////////�m�F�p�I�u�W�F�N�g�\��////////////
	/*Pointer* pPointer = (Pointer*)FindChild("Pointer");
	XMFLOAT3 po;
	XMStoreFloat3(&po, vPosition_+frontVec_);
	pPointer->SetPointerPos(po);*/
	//pPointer->SetDraw(true);
	
	////////////////�G�l�~�[�̏���/////////////
	XMVECTOR toPlayer;
	XMFLOAT3 aa = pPlayer_->GetPosition();		//�v���C���[�̍��W�擾
	toPlayer = XMLoadFloat3(&aa) - vPosition_;	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����쐬

	if (IsVisible(frontVec_,XMLoadFloat3(&aa),0.5,50.0f)/*&&visibleFlag_*/)
	{
		EnemyMove(toPlayer);
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

void EnemyNormal::EnemyMove(XMVECTOR toVec)
{
	vPosition_ = XMLoadFloat3(&transform_.position_);			//vPosition�ɍ��̍��W������
	toVec = XMVector3Normalize(toVec);							//�����̐��K��
	float angle = XMVectorGetX(XMVector3Dot(frontVec_, toVec)); //�p�x�v�Z(���W�A��)
	matY_ = XMMatrixRotationY(1-angle);							//�p�x����]�s��ɕϊ�
	frontVec_ = XMVector3TransformCoord(toVec, matY_);			//�O�����x�N�g������]
	
	vPosition_ += toVec*0.3f;
	XMStoreFloat3(&transform_.position_, vPosition_);
}

bool EnemyNormal::IsVisible(XMVECTOR vFront, XMVECTOR vTarget, float visibleAngle,float range)
{
	vFront = XMVector3Normalize(vFront);								//���K��
	XMVECTOR toVector = vTarget - XMLoadFloat3(&transform_.position_);	//�ڕW�Ɍ������x�N�g��
	float rangeToPlayer;
	rangeToPlayer = XMVectorGetX(XMVector3Length(toVector));			//���E����p�̎��E�̒����擾
	toVector = XMVector3Normalize(toVector);							//���K��

	XMVECTOR dot = XMVector3Dot(vFront, toVector);						//���ς��v�Z
	float angle = acos(min(XMVectorGetX(dot),1));						//�p�x�v�Z(1�ȏ�ɂȂ�Ȃ��悤min�֐�����)

	if (angle<visibleAngle && angle>-visibleAngle && rangeToPlayer < range)
	{
		return true;
	}

	return false;
}

void EnemyNormal::OnCollision(GameObject* pTarget)
{

}

//�J��
void EnemyNormal::Release()
{
}