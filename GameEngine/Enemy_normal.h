#pragma once
#include"Enemy.h"
#include"Player.h"

class Enemy_normal : public Enemy
{
private:
    int hModel_;

    XMMATRIX matX_;
    XMMATRIX matY_;
    

    XMVECTOR frontVec_;
    XMVECTOR vPosition_;
    Player* pPlayer_;
public:
    //�R���X�g���N�^
    Enemy_normal(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy_normal();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void FixedUpdate() override;
    //�`��
    void Draw() override;

    //�G�l�~�[������
    void EnemyMove(XMVECTOR toVec);

    bool IsVisible(XMVECTOR vFront, XMVECTOR vTarget,float angle1,float angle2);

    //�J��
    void Release() override;
};