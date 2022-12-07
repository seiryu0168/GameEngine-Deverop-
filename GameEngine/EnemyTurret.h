#pragma once
#include "Enemy.h"
class EnemyTurret : public Enemy
{
private:
    int hModel_;

    float targetingRange_;
    float viewangle_;

public:
    //�R���X�g���N�^
    EnemyTurret(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyTurret();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void FixedUpdate() override;

    //�`��
    void Draw() override;

    //���
    void Release() override;
};

