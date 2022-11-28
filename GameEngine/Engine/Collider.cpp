#include "Collider.h"
#include"BoxCollider.h"
#include"SphereCollider.h"
#include"GameObject.h"
#include"Fbx.h"

Collider::Collider()
{
	pColObject_ = nullptr;
}
Collider::~Collider()
{

}

//BoxとBoxの当たり判定
bool Collider::IsHitBox_Box(BoxCollider* boxB, BoxCollider* boxA)
{
	//BoxPosにFloat3Addの戻り値を入れる
	//引数
	//自分の座標
	//相手の座標

	XMFLOAT3 boxPos1 = Transform::Float3Add(boxA->pColObject_->GetWorldPosition(), boxA->center_);
	XMFLOAT3 boxPos2 = Transform::Float3Add(boxB->pColObject_->GetWorldPosition(), boxB->center_);

	if ((boxPos1.x + boxA->size_.x/ 2) > (boxPos2.x - boxB->size_.x / 2) &&
		(boxPos1.x - boxA->size_.x / 2) < (boxPos2.x + boxB->size_.x / 2) &&
		(boxPos1.y + boxA->size_.y / 2) > (boxPos2.y - boxB->size_.y / 2) &&
		(boxPos1.y - boxA->size_.y / 2) < (boxPos2.y + boxB->size_.y / 2) &&
		(boxPos1.z + boxA->size_.z / 2) > (boxPos2.z - boxB->size_.z / 2) &&
		(boxPos1.z - boxA->size_.z / 2) < (boxPos2.z + boxB->size_.z / 2))
	{
		return true;
	}

	return false;

}

//BoxとSphereの当たり判定
bool Collider::IsHitBox_Sphere(BoxCollider* box, SphereCollider* sphere)
{
	XMFLOAT3 boxPos = Transform::Float3Add(box->pColObject_->GetWorldPosition(), box->center_);
	XMFLOAT3 spherePos= Transform::Float3Add(sphere->pColObject_->GetWorldPosition(), sphere->center_);

	if (spherePos.x > boxPos.x - box->size_.x - sphere->size_.x &&
		spherePos.x < boxPos.x + box->size_.x + sphere->size_.x &&
		spherePos.y > boxPos.y - box->size_.y - sphere->size_.x &&
		spherePos.y < boxPos.y + box->size_.y + sphere->size_.x &&
		spherePos.z > boxPos.z - box->size_.z - sphere->size_.x &&
		spherePos.z < boxPos.z + box->size_.z + sphere->size_.x)
	{
		return true;
	}

	return false;
}

//SphereとSphereの当たり判定
bool Collider::IsHitSphere_Sphere(SphereCollider* sphereA, SphereCollider* sphereB)
{
	XMFLOAT3 spherePosA = sphereA->center_;
	XMFLOAT3 positionA = sphereA->pColObject_->GetWorldPosition();
	XMFLOAT3 spherePosB = sphereB->center_;
	XMFLOAT3 positionB = sphereB->pColObject_->GetWorldPosition();

	XMVECTOR vec = (XMLoadFloat3(&spherePosA) + XMLoadFloat3(&positionA)) - (XMLoadFloat3(&spherePosB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(vec).m128_f32[0] <= sphereA->size_.x + sphereB->size_.x)
	{
		return true;
	}
	return false;

}

bool IsHitOBB_OBB(OBBCollider* obbA, OBBCollider* obbB)
{

}