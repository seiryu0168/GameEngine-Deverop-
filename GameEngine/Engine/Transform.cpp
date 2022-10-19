#include "Transform.h"

//�R���X�g���N�^
Transform::Transform()
{
	matTranslate_=XMMatrixIdentity();
	matRotate_=XMMatrixIdentity();
	matScale_=XMMatrixIdentity();
	position_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotate_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
	pParent_ = nullptr;
}

//�f�X�g���N�^
Transform::~Transform()
{

}

//�e�s��̌v�Z
void Transform::Calclation()
{
	//�ړ��s��
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
	
	//��]�s��
	matRotate_ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z)) 
			   * XMMatrixRotationX(XMConvertToRadians(rotate_.x)) 
			   * XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	
	//�g��s��
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

//�t�s��̌v�Z
XMMATRIX Transform::GetNormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}

//���[���h�s����擾
XMMATRIX Transform::GetWorldMatrix()
{
	Calclation();
	if (pParent_)
	{
		return matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}
	return matScale_ * matRotate_ * matTranslate_;

}

XMMATRIX Transform::GetRotateMatrix()
{
	return matRotate_;
}
XMMATRIX Transform::GetScaleMatrix()
{
	return matScale_;
}