#include "Player.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/SceneManager.h"
#include"EngineTime.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)

{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    transform_.position_ = XMFLOAT3(-2.0f, 0.0f, 0.0f);
    hModel_ = Model::Load("Assets\\TestBox.fbx");
    assert(hModel_ >= 0);
    BoxCollider* pCollider = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1,4,1));
    AddCollider(pCollider);
}

//�X�V
void Player::Update()
{
    if (Input::IsPadButton(XINPUT_GAMEPAD_A))
    {
        int a = 10;
    }
}

void Player::FixedUpdate()
{
   
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}


void Player::OnCollision(GameObject* pTarget)
{
    //KillMe();
}