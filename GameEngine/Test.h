#pragma once
#include "Engine//GameObject.h"
#include"Engine/Fbx.h"
#include"BillBoard.h"

class Test : public GameObject
{
    int hModel_;
    //BillBoard aaa;
    //int hBill = aaa.Load("Assets\\bluefire.png");
public:
    //�R���X�g���N�^
    Test(GameObject* parent);

    //�f�X�g���N�^
    ~Test();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;
    void FixedUpdate() override;
    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};

