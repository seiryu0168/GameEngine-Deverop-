#include "Player.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Stage1.h"
#include"Pointer.h"
#include"Engine/SceneManager.h"
#include"EngineTime.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),
    hModel_(-1),
    vCamPos_(XMVectorSet(0, 5, -15, 0)),
    vPlayerPos_(XMVectorSet(0,0,0,0)),
    vBaseTarget_(XMVectorSet(0,0,5,0)),
    matCamX_(XMMatrixIdentity()),
    matCamY_(XMMatrixIdentity()),
    velocity_(5),
    speed_(4.0f),
    angleY_(0),
    angleX_(0),
    flyFlag_(false)

{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    hModel_ = Model::Load("Assets\\TestBox.fbx");
    assert(hModel_ >= 0);
   
    BoxCollider* pCollider = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 4, 1));
    AddCollider(pCollider);
    stageNum_ = ((Stage1*)GetParent()->FindChild("Stage1"))->GetModelHandle();
    
    Instantiate<Pointer>(this);

    transform_.position_ = XMFLOAT3(0, 20,0);
    RayCastData firstRay;
    firstRay.start = transform_.position_;
    
    rayDir_[0] = XMVectorSet( 0, 0, 1, 0);
    rayDir_[1] = XMVectorSet( 0, 0,-1, 0);
    rayDir_[2] = XMVectorSet(-1, 0, 0, 0);
    rayDir_[3] = XMVectorSet( 1, 0, 0, 0);
    rayDir_[4] = XMVectorSet( 0, 1, 0, 0);
    rayDir_[5] = XMVectorSet( 0,-1, 0, 0);
    
    XMStoreFloat3(&firstRay.dir,rayDir_[DIR_DOWN]);
    Model::RayCast(stageNum_, firstRay);

    if (firstRay.hit)
    {
        //transform_.position_.y -= firstRay.dist-transform_.scale_.y;
    }
}

//�X�V
void Player::Update()
{
    vPlayerPos_ = XMLoadFloat3(&transform_.position_);

    Pointer* pPointer = (Pointer*)FindChild("Pointer");
    pPointer->SetDraw(false);
    RayCastData ray;
    
    //�g���K�[�������ƈړ��ł���ǂɃ}�[�J�[���\�������
    if (Input::GetLTrigger())
    {
        //������ʒu�̌v�Z
        XMVECTOR vPtrBack = XMVector3TransformCoord(vBaseTarget_, matCamY_ * matCamX_);

        XMStoreFloat3(&ray.start, vPlayerPos_);
        XMStoreFloat3(&ray.dir, vPtrBack);
        Model::RayCast(stageNum_, ray);
        
        //���������ʒu�ɕ\��
        if (ray.hit)
        {
            XMFLOAT3 pointerPos;
            XMStoreFloat3(&pointerPos, ray.hitPos);
            pPointer->SetPointerPos(pointerPos);
            pPointer->SetDraw(ray.hit);
        }
    }

    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && pPointer->IsDraw())
    {
        if (ray.hit)
        {
            vFlyMove_ = XMVector3Normalize(ray.hitPos - vPlayerPos_)*2;
            airFlag_ = false;
            flyFlag_ = true;
        }
    }

    else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && airFlag_ == false)
    {
        velocity_ = 2;
        airFlag_ = true;
    }

    XMVECTOR vMove = XMVectorSet(0, 0, 0, 0);
        vMove = XMVectorSet(Input::GetLStick_X(), 0, Input::GetLStick_Y(), 0);
        vMove = XMVector3TransformCoord(vMove, matCamX_);

            XMVECTOR vFly = XMVectorSet(0, 0, 0, 0);
    if (flyFlag_)
    {
        vFly = vFlyMove_;
    }
    vMove += XMVectorSet(0, velocity_, 0, 0);

    velocity_ -= 0.06;



    XMVECTOR vPlayerMove = XMVectorSet(0, 0, 0, 0);
    vPlayerMove = vMove + vFly;
    CharactorControll(vPlayerMove);
    XMStoreFloat3(&transform_.position_, vPlayerPos_ + vPlayerMove);
    CameraMove();

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

void Player::CameraMove()
{
    angleX_ += Input::GetRStick_Y() * speed_;
    angleY_ += Input::GetRStick_X() * speed_;
    transform_.rotate_.y = angleY_;
    vPlayerPos_ = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMoveCam;
    XMVECTOR vTarCam;
    if (angleX_ <= -90)
    {
        angleX_ = -89;
    }
    if (angleX_ >= 70)
    {
        angleX_ = 69;
    }
    matCamY_ = XMMatrixRotationX(angleX_ * (M_PI / 180));
    matCamX_ = XMMatrixRotationY(angleY_ * (M_PI / 180));
    vMoveCam = XMVector3TransformCoord(vCamPos_,     matCamY_ * matCamX_);
    vTarCam  = XMVector3TransformCoord(vBaseTarget_, matCamY_ * matCamX_);

    Camera::SetTarget   (vPlayerPos_ + vTarCam);
    Camera::SetPosition(vPlayerPos_ + vMoveCam);
}

void Player::Jump()
{

}

void Player::CharactorControll(XMVECTOR &moveVector)
{
    RayCastData FRay;
    RayCastData BRay;
    RayCastData LRay;
    RayCastData RRay;
    RayCastData URay;
    RayCastData DRay;
    FRay.start = transform_.position_;
    BRay.start = transform_.position_;
    LRay.start = transform_.position_;
    RRay.start = transform_.position_;
    URay.start = transform_.position_;
    DRay.start = transform_.position_;
    
    XMStoreFloat3(&FRay.dir, rayDir_[DIR_FRONT]);
    XMStoreFloat3(&BRay.dir, rayDir_[DIR_BACK]);
    XMStoreFloat3(&LRay.dir, rayDir_[DIR_LEFT]);
    XMStoreFloat3(&RRay.dir, rayDir_[DIR_RIGHT]);    
    XMStoreFloat3(&URay.dir, rayDir_[DIR_UP]);    
    XMStoreFloat3(&DRay.dir, rayDir_[DIR_DOWN]);    

    Model::RayCast(stageNum_, FRay);
    Model::RayCast(stageNum_, BRay);
    Model::RayCast(stageNum_, LRay);
    Model::RayCast(stageNum_, RRay);
    Model::RayCast(stageNum_, URay);
    Model::RayCast(stageNum_, DRay);

    XMFLOAT3 moveDist;
    XMStoreFloat3(&moveDist,moveVector);

    //�O�����C�̋���(dist)��1�ȉ��ɂȂ�����z���̍��W��߂�
    if (moveDist.z+transform_.scale_.z >= FRay.dist)
    {
        transform_.position_.z += FRay.dist - 1.0f;
        moveDist.z = FRay.dist-1.0f;
        //flyFlag_ = false;
    }
    
    //������C�̋���(dist)��1�ȉ��ɂȂ�����z���̍��W��߂�
    if (abs(moveDist.z-transform_.scale_.z) >= BRay.dist)
    {
        transform_.position_.z -= BRay.dist + 1.0f;
        moveDist.z = 0;
        //flyFlag_ = false;
    }

    //�E���C�̋���(dist)��1�ȉ��ɂȂ�����x���̍��W��߂�
    if (moveDist.x+transform_.scale_.x >= RRay.dist)
    {
        transform_.position_.x += RRay.dist - 1.0f;
        moveDist.x = 0;
            //flyFlag_ = false;
    }

    //�����C�̋���(dist)��1�ȉ��ɂȂ�����x���̍��W��߂�
    if (abs(moveDist.x-transform_.scale_.x) >= LRay.dist)
    {
        transform_.position_.x -= LRay.dist + 1.0f;
        moveDist.x = 0;
        //flyFlag_ = false;
    }
    //�ヌ�C�̋���(dist)��1�ȉ��ɂȂ�����x���̍��W��߂�
    if (moveDist.y - transform_.scale_.y >= URay.dist)
    {
        transform_.position_.y += URay.dist + 1.0f;
        moveDist.y = 0;
        //flyFlag_ = false;
    }

    //�����C�̋���(dist)��1�ȉ��ɂȂ����玲�̍��W��߂�
    if (abs(moveDist.y-transform_.scale_.y) >= DRay.dist)
    {

        transform_.position_.y -= DRay.dist+1.0f;
        moveDist.y = 0;
        flyFlag_ = false;
        airFlag_ = false;
        velocity_ = -1;

    }

    moveVector = XMLoadFloat3(&moveDist);

    
}

void Player::OnCollision(GameObject* pTarget)
{
    //KillMe();
}