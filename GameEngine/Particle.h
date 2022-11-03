#pragma once
#include"Engine/GameObject.h"

struct EmitterData
{
    
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

