#pragma once
#include"Enemy.h"
class EnemyBoss : public Enemy
{
    int hModel_;

public:
    //�R���X�g���N�^
    EnemyBoss(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyBoss();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void FixedUpdate() override;
    //�`��
    void Draw() override;

    void Attack() override;

    //�G�l�~�[�̓���
    //���������x�N�g��
    void EnemyMove();

    //�J��
    void Release() override;

    //�Փ�
    void OnCollision(GameObject* pTarget) override;
};

