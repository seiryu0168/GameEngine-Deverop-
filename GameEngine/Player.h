#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"

class Player : public GameObject
{
    XMVECTOR rayDir[6];

    int hModel_;
    int stageNum_;
    bool flyFlag;
    XMVECTOR vCamPos;
    XMVECTOR vPlayerPos;
    //XMVECTOR vPlayerMove;
    XMVECTOR vBaseTarget;
    XMVECTOR vFlyMove;
    XMMATRIX matCamX;
    XMMATRIX matCamY;
    float speed;
    float angleY;
    float angleX;

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

    void CharactorControll(XMVECTOR &moveVector);

    void CameraMove();

    void OnCollision(GameObject* pTarget) override; 
};

