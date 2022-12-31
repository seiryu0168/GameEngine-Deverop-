#pragma once
#include"Engine/GameObject.h"
#include"Engine/BillBoard.h"
class Player;

class HomingBullet : public GameObject
{
    int hModel_;
    int life_;
    float speed_;
    XMVECTOR position_;
    XMVECTOR velocity_;
    Player* pPlayer_;
    BillBoard* pBill_;
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

    void SetDir(XMVECTOR dir) { dir_ = dir; }
    //�`��
    void Draw() override;

    void OnCollision(GameObject* target) override;

    void Release() override;
};

