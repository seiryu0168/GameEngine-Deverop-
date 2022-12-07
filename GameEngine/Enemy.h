#pragma once
#include"Engine/GameObject.h"
#include"EnemyState.h"
#include"Player.h"
class Enemy : public GameObject
{
protected:
    EnemyState* pEnemyState_;

    bool     visibleFlag_;  //�v���C���[�������Ă��邩�ǂ���
    bool     isTargetList_; //�v���C���[�̃^�[�Q�b�g���X�g�ɓ����Ă邩�ǂ���

    int      life_;         //�G�̗̑�

    XMMATRIX matX_;         //X���̉�]�s��
    XMMATRIX matY_;         //Y���̉�]�s��
    XMVECTOR toPlayerVec_;  //�v���C���[�Ɍ������x�N�g��
    XMVECTOR upVec_;        //������x�N�g��(�v���C���[�Ƃ̈ʒu�֌W�����߂鎞�Ɏg�����肷��)
    XMVECTOR vPosition_;    //���݈ʒu�̃x�N�g��
    Player* pPlayer_;      //�v���C���[�̃|�C���^
    //�R���X�g���N�^
    Enemy(GameObject* parent,std::string name);

    //�f�X�g���N�^
    ~Enemy();
public:
    XMVECTOR frontVec_;     //�O�����x�N�g��(���̃x�N�g������ɂ��Ď��E�����܂�)
    void ChangeState(EnemyState* state);
    bool IsVisible(XMVECTOR front,float angle,float range);
    virtual void Attack()=0;
    XMMATRIX GetMatrixX() { return matX_; }
    XMMATRIX GetMatrixY() { return matY_; }
    XMVECTOR GetToPlayerVec() { return toPlayerVec_; }
    XMVECTOR GetUpVec() { return upVec_; }
    Player* GetPlayerPointer() { return pPlayer_; }
    //isTargetList�̃t���O�擾
    bool GetIsList() { return isTargetList_; }

};

