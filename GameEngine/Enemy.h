#pragma once
#include"Engine/GameObject.h"
#include"EnemyState.h"
#include"Player.h"
struct parameter
{
    bool     visibleFlag;  //�v���C���[�������Ă��邩�ǂ���
    bool     isTargetList; //�v���C���[�̃^�[�Q�b�g���X�g�ɓ����Ă邩�ǂ���

    int      life;         //�G�̗̑�

    XMMATRIX matX;         //X���̉�]�s��
    XMMATRIX matY;         //Y���̉�]�s��
    XMVECTOR frontVec;     //�O�����x�N�g��(���̃x�N�g������ɂ��Ď��E�����܂�)
    XMVECTOR toPlayerVec;  //�v���C���[�Ɍ������x�N�g��
    XMVECTOR upVec;        //������x�N�g��(�v���C���[�Ƃ̈ʒu�֌W�����߂鎞�Ɏg�����肷��)
    XMVECTOR vPosition;    //���݈ʒu�̃x�N�g��
    Player* pPlayer;      //�v���C���[�̃|�C���^
};

class Enemy : public GameObject
{
private:
    parameter enemyParameter_;
    EnemyState* pEnemyState_;
    //�R���X�g���N�^
    Enemy(GameObject* parent,std::string name);

    //�f�X�g���N�^
    ~Enemy();
public:
    void ChangeState(EnemyState* state);
    bool IsVisible(XMVECTOR front,float angle,float range);
    virtual void Attack()=0;
    void SetToPlayerVec(XMVECTOR vec) { enemyParameter_.toPlayerVec = vec; }
    void SetPositionVec(XMVECTOR vec) { enemyParameter_.vPosition = vec; }
    void SetFrontVec(XMVECTOR vec) { enemyParameter_.frontVec = vec; }
    void SetMatrixX(XMMATRIX mat) { enemyParameter_.matX = mat; }
    void SetMatrixY(XMMATRIX mat) { enemyParameter_.matY = mat; }



    XMMATRIX GetMatrixX() { return enemyParameter_.matX; }
    XMMATRIX GetMatrixY() { return enemyParameter_.matY; }
    XMVECTOR GetToPlayerVec() { return enemyParameter_.toPlayerVec; }
    XMVECTOR GetPositionVec() { return enemyParameter_.vPosition; }
    XMVECTOR GetUpVec() { return enemyParameter_.upVec; }
    XMVECTOR GetFrontVec() { return enemyParameter_.frontVec; }
    Player* GetPlayerPointer() { return enemyParameter_.pPlayer; }
    //isTargetList�̃t���O�擾
    bool GetIsList() { return enemyParameter_.isTargetList; }

};

