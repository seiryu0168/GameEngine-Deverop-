#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"

class Player : public GameObject
{
    enum DIR_NAME
    {
        DIR_FRONT=0,
        DIR_BACK,
        DIR_LEFT,
        DIR_RIGHT,
        DIR_UP,
        DIR_DOWN
    };
    XMVECTOR rayDir_[6];
    int hModel_;
    int stageNum_;
    bool flyFlag_;
    bool airFlag_;

    XMVECTOR vCamPos_;
    XMVECTOR vPlayerPos_;
    XMVECTOR vBaseTarget_;
    XMVECTOR vFlyMove_;
    XMVECTOR vBaseAim_;
    XMMATRIX matCamX_;
    XMMATRIX matCamY_;

    float trrigerPower_;
    float velocity_;
    float speed_;
    float angleY_;
    float angleX_;

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void FixedUpdate() override;
    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Jump();

    void CharactorControll(XMVECTOR &moveVector);

    void CameraMove(RayCastData ray);

    void OnCollision(GameObject* pTarget) override; 
};

