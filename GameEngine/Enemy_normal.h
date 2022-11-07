#pragma once
#include"Enemy.h"
#include"Player.h"

class Enemy_normal : public Enemy
{
public:
    int hModel_;

    XMVECTOR moveVec_;
    XMMATRIX matX_;
    XMMATRIX matY_;

    Player* pPlayer_;
private:
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

    //
    void EnemyRotate(XMVECTOR toVec);

    //�J��
    void Release() override;
};