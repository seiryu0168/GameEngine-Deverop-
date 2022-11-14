#pragma once
#include"Engine/GameObject.h"
class Pointer : public GameObject
{

private:
    int hModel_;
    bool drawFlag_;
    short objectType_;
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

    //�Փ�
    void OnCollision(GameObject* pTarget);

    //�J��
    void  Release() override;
    bool  IsDraw() { return drawFlag_; }
    void  SetDraw(bool flag) { drawFlag_ = flag; }
    short GetObjectType();
    void  SetPointerPos(XMFLOAT3 position);
};

