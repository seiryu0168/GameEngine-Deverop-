#include "Enemy_normal.h"
#include"Engine/Model.h"
//�R���X�g���N�^
Enemy_normal::Enemy_normal(GameObject* parent)
	:Enemy(parent,"Enemy_normal"),
	hModel_(-1),
	moveVec_(XMVectorSet(0,0,1,0)),
	matX_(XMMatrixIdentity()),
	matY_(XMMatrixIdentity()),
	pPlayer_(nullptr)
{

}

//�f�X�g���N�^
Enemy_normal::~Enemy_normal()
{

}

//������
void Enemy_normal::Initialize()
{
	hModel_ = Model::Load("Assets\\Box.fbx");
	pPlayer_ = (Player*)FindObject("Player");
}

//�X�V
void Enemy_normal::Update()
{

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

void Enemy_normal::EnemyRotate(XMVECTOR toVec)
{
	XMVECTOR toVector;
	toVector = toVec - XMLoadFloat3(&transform_.position_);
}

//�J��
void Enemy_normal::Release()
{

}