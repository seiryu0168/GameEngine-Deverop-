#include "EnemyTurret.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
//�R���X�g���N�^
EnemyTurret::EnemyTurret(GameObject* parent)
	:Enemy(parent,"EnemyTurret"),
	targetingRange_(70.0f),
	viewangle_(90.0f)
{

}

//�f�X�g���N�^
EnemyTurret::~EnemyTurret()
{

}

//������
void EnemyTurret::Initialize()
{
	hModel_ = Model::Load("Assets\\Enemy2.fbx");
	assert(hModel_ >= 0);


}

//�X�V
void EnemyTurret::Update()
{

}

void EnemyTurret::Attack()
{

}

void EnemyTurret::FixedUpdate()
{

}
//�`��
void EnemyTurret::Draw()
{

}

void EnemyTurret::Release()
{

}