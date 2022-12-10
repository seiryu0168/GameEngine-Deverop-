#pragma once
#include "Engine/GameObject.h"
#include"Engine/BillBoard.h"
class Bullet : public GameObject
{
private:
    int hModel_;
    int life_;
    float speed_;

    BillBoard* pBill_;
    XMVECTOR dir_;

public:
    //�R���X�g���N�^
    Bullet(GameObject* parent);

    //�f�X�g���N�^
    ~Bullet();

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

