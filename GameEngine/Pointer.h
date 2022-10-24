#pragma once
#include"Engine/GameObject.h"
class Pointer : public GameObject
{

private:
    int hModel_;
    bool drawFlag_;
public:
    Pointer(GameObject* parent);

    //�f�X�g���N�^
    ~Pointer();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void FixedUpdate() override;
    //�`��
    void Draw() override;

    //�J��
    void Release() override;
    void IsDraw(bool flag) { drawFlag_ = flag; }
    void SetPointerPos(XMFLOAT3 position);
};

