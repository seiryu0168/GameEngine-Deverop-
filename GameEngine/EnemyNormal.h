#pragma once
#include"Enemy.h"

class EnemyNormal : public Enemy
{
private:
    int      hModel_;       //���f���ԍ�

public:
    //�R���X�g���N�^
    EnemyNormal(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyNormal();

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