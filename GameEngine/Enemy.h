#pragma once
#include"Engine/GameObject.h"
class Enemy : public GameObject
{
protected:
    //�R���X�g���N�^
    Enemy(GameObject* parent,std::string name);

    //�f�X�g���N�^
    ~Enemy();
};

