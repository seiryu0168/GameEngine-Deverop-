#pragma once
#include"Enemy.h"
//#include"Engine/GameObject.h"
class Enemy_normal : public Enemy
{
public:
    int hModel_;
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

    //�J��
    void Release() override;
};