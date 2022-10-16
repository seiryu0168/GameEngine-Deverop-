#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"

class Player : public GameObject
{
    int hModel_;
    int stageNum_;
    XMVECTOR vCamPos;
    XMVECTOR vPlayerPos;
    XMVECTOR vPlayerMove;
    XMVECTOR vBaseTarget;
    XMMATRIX matCam;
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

    void CameraMove();

    void OnCollision(GameObject* pTarget) override; 
};

