#include "PlayerEnemyState.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
PlayerState::PlayerState(Player* player)
{
	pPlayer_ = player;
}

void PlayerState::Initialize()
{
}

void PlayerState::Update()
{
    //RayCastData ray;

    //if (Input::GetLTrigger())
    //{
    //    //���C�L���X�g�̔��苗���̏��
    //    ray.distLimit = 100.0f;
    //    aimFlag_ = true;
    //    //������ʒu�̌v�Z
    //    XMVECTOR vPlayerDir = XMVector3TransformCoord(vBaseTarget_, matCamY_ * matCamX_);
    //    XMVECTOR vPtrDir = vPlayerDir;
    //    XMStoreFloat3(&ray.start, pPlayer_->vPlayerPos_);
    //    XMStoreFloat3(&ray.dir, vPtrDir);

    //    //�G�C���A�V�X�g�͈͓����ǂ�������
    //    if (enemyList_.size() > 0/*&&IsAssistRange(vPlayerDir, pEnemy->GetTransform().position_,ray.distLimit)*/)
    //    {
    //        EnemyNormal* pEnemy = pPlayer_->AimAssist(&ray);
    //        if (pEnemy != nullptr)
    //        {
    //            vPtrDir = XMVector3TransformCoord(vPtrDir, LookAtMatrix(pEnemy->GetTransform().position_, vPtrDir));
    //            XMStoreFloat3(&ray.dir, vPtrDir);
    //        }
    //    }

    //    //���C�L���X�g�̎n�_�ƕ��������
    //    Model::RayCast(ray);

    //    //���������ʒu�Ƀ}�[�J�[�\��
    //    if (ray.hit && !flyFlag_)
    //    {
    //        rotateSpeed_ = 2.0f;
    //        XMFLOAT3 pointerPos;
    //        XMStoreFloat3(&pointerPos, ray.hitPos);
    //        pPointer->SetPointerPos(pointerPos);
    //        pPointer->SetDraw(ray.hit);
    //    }
    //}
}

EnemyState::EnemyState(Enemy* enemy)
	:EnemyState(enemy)
{
	pEnemy_ = enemy;
}

void EnemyState::Initialize()
{

}

void EnemyState::Update()
{

}