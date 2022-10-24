#include "Pointer.h"
#include"Engine/Model.h"
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
	hModel_ = Model::Load("Assets\\Mark.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Pointer::Update()
{

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

void Pointer::SetPointerPos(XMFLOAT3 position)
{
	transform_.position_ = position;
}

//�J��
void Pointer::Release()
{

}