#pragma once
#include "Enemy.h"
class EnemyTurret : public Enemy
{
private:
    int hModel_;
    int shotTime_;
    float rpm_;//�A�ˑ��x Rounds Per Minute

public:
    //�R���X�g���N�^
    EnemyTurret(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyTurret();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void Attack() override;
    void FixedUpdate() override;

    void Shot();
    //�`��
    void Draw() override;

    //���
    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};

