#pragma once
#include"Engine/GameObject.h"
#include"EnemyState.h"
#include"Player.h"
struct parameter
{
    bool     visibleFlag;  //�v���C���[�������Ă��邩�ǂ���
    bool     isTargetList; //�v���C���[�̃^�[�Q�b�g���X�g�ɓ����Ă邩�ǂ���

    int      life;         //�G�̗̑�

    float    viewRange;
    float    viewAngle;

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
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent,std::string name);

    //�f�X�g���N�^
    ~Enemy();
    
    virtual void Attack()=0;
    
    bool IsVisible(float angle,float range);//�w�肵��������Ƀv���C���[�����邩�ǂ��� : ���p�A�����鋗��
    void ChangeState(EnemyState* state);
    void SetviewRange(float range) { enemyParameter_.viewRange = range; }
    void SetviewAngle(float angle) { enemyParameter_.viewAngle = angle; }
    void SetToPlayerVec(XMVECTOR vec) { enemyParameter_.toPlayerVec = vec; }
    void SetPositionVec(XMVECTOR vec) { enemyParameter_.vPosition = vec; }
    void SetFrontVec(XMVECTOR vec) { enemyParameter_.frontVec = vec; }
    void SetMatrixX(XMMATRIX mat) { enemyParameter_.matX = mat; }
    void SetMatrixY(XMMATRIX mat) { enemyParameter_.matY = mat; }
    void SetPlayerPointer(Player* pointer) { enemyParameter_.pPlayer = pointer; }
    void SetLife(int life) { enemyParameter_.life = life; }
    void DecreaseLife(int decRate) { enemyParameter_.life -= decRate; }
    void IncreaseLife(int incRate) { enemyParameter_.life += incRate; }

    float GetViewAngle() { return enemyParameter_.viewAngle; }
    float GetViewRange() { return enemyParameter_.viewRange; }
    XMMATRIX GetMatrixX() { return enemyParameter_.matX; }
    XMMATRIX GetMatrixY() { return enemyParameter_.matY; }
    XMVECTOR GetToPlayerVec() { return enemyParameter_.toPlayerVec; }
    XMVECTOR GetPositionVec() { return enemyParameter_.vPosition; }
    XMVECTOR GetUpVec() { return enemyParameter_.upVec; }
    XMVECTOR GetFrontVec() { return enemyParameter_.frontVec; }
    Player* GetPlayerPointer() { return enemyParameter_.pPlayer; }
    bool GetIsList() { return enemyParameter_.isTargetList; }
    int GetLife() { return enemyParameter_.life; }
    EnemyState* GetEnemyState() { return pEnemyState_; }

};

