#pragma once
#include"Engine/GameObject.h"

struct EmitterData
{
    std::string textureFileName;    //�\��e�N�X�`���̃t�@�C����
    XMFLOAT3 position;              //�G�~�b�^�[�̈ʒu
    XMFLOAT3 positionErr;           //�G�~�b�^�[�̌덷
    XMFLOAT3 dir;                   //�p�[�e�B�N���̔��˕���
    XMFLOAT3 dirErr;                //�p�[�e�B�N���̔��˕����̌덷
    float speed;                    //1�t���[��������̈ړ���
    float speedErr;                 //�ړ��ʂ̌덷
    float acceleration;             //�����x
    float gravity;                  //�d��
    XMFLOAT4 color;                 //�F : RGBA 0�`�P
    XMFLOAT4 deltaColor;            //�F�̕ω���
    XMFLOAT2 size;                  //�T�C�Y
    XMFLOAT2 sizeErr;               //�T�C�Y�̌덷
    XMFLOAT2 scale;                 //1�t���[��������̊g�嗦
    float lifTime;                  //�p�[�e�B�N���̎���
    
    int delay;                      //�p�[�e�B�N�����o���Ԋu�̃t���[����
    int number;                     //1��ɏo���p�[�e�B�N���̐�

//Emitter������
        EmitterData()
        {
            textureFileName = "";
            position = positionErr = dir = dirErr = { 0,0,0 };
            speed = 0.0f;
            acceleration = 1.0f;
            gravity = 0.0f;
            color = { 1,1,1,1 };
            deltaColor = { 0,0,0,0 };
            size = scale = { 1.0f,1.0f };
            lifTime = 10.0f;
        }

};
class Particle : public GameObject
{
private:
    int hModel_;
    float lifeTime_;
     XMFLOAT3 particleScale_;
     XMFLOAT3 particleRotate_;

public:
    Particle(GameObject* parent);

    //�f�X�g���N�^
    ~Particle();

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

