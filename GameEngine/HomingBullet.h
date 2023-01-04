#pragma once
#include"Engine/GameObject.h"
#include"Engine/BillBoard.h"
class Player;
class Particle;
class HomingBullet : public GameObject
{
    int hModel_;
    int life_;
    int period_;
    float speed_;
    XMVECTOR position_;
    XMVECTOR velocity_;
    Player* pPlayer_;
    BillBoard* pBill_;
    Particle* pParticle_;
    XMVECTOR dir_;

public:
    //�R���X�g���N�^
    HomingBullet(GameObject* parent);

    //�f�X�g���N�^
    ~HomingBullet();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void FixedUpdate() override;

    void Homing();
    void SetDir(XMVECTOR dir) { dir_ = dir; }
    //�`��
    void Draw() override;
    void BeforeDeath() override;

    void OnCollision(GameObject* target) override;

    void Release() override;
};

