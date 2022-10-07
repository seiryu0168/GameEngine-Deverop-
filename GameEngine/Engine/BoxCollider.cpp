#include "BoxCollider.h"

BoxCollider::BoxCollider(XMFLOAT3 basePos, XMFLOAT3 size)
{
	center_ = basePos;
	size_ = size;
	/*scaleX_ = XMVectorSet(size.x, 0, 0, 0);
	scaleY_ = XMVectorSet(0, size.y, 0, 0);
	scaleZ_ = XMVectorSet(0, 0, size.z, 0);*/
	type_ = BOX_COLLIDER;
}

//�Փ˔���
//���������I�u�W�F�N�g�̓����蔻�肪target�ɓ���
bool BoxCollider::IsHit(Collider* target)
{
	if (target->type_ == BOX_COLLIDER)
	{
		return IsHitBox_Box((BoxCollider*)target, this);
	}
	else
		return IsHitBox_Sphere(this, (SphereCollider*)target);
}