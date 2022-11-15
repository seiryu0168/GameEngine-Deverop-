#include "Pointer.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
Pointer::Pointer(GameObject* parent)
	:GameObject(parent,"Pointer"),
	drawFlag_(false)
{

}

//�f�X�g���N�^
Pointer::~Pointer()
{

}

//������
void Pointer::Initialize()
{
	SphereCollider* pCollision = new SphereCollider({ 0,0,0 }, 1);
	AddCollider(pCollision);
	hModel_ = Model::Load("Assets\\Mark.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Pointer::Update()
{

	objectType_ = -1;
}

void Pointer::FixedUpdate()
{

}
//�`��
void Pointer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	
	if (drawFlag_)
	{
		Model::Draw(hModel_);
	}
}

short Pointer::GetObjectType()
{
	return objectType_;
}


void Pointer::SetPointerPos(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void Pointer::OnCollision(GameObject* pTarget)
{
	if (drawFlag_)
	{
		if (pTarget->GetObjectName() == "EnemyNormal")
		{
			objectType_ = ATC_ATTACK;
		}
	}
}

//�J��
void Pointer::Release()
{

}