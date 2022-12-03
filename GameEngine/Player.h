#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"


class Particle;
class EnemyNormal;
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

    int playerLife_;

    XMVECTOR baseUpVec_;
    XMVECTOR rayDir_[6];

    const float gravity_;

    int hModel_;
    int stageNum_;

    bool flyFlag_;
    bool airFlag_;
    bool aimFlag_;
    bool jumpFlag_;
    bool groundFlag_;

    XMVECTOR vCamPos_;
    XMVECTOR vPlayerPos_;
    XMVECTOR vPlayerMove_;
    XMVECTOR vBaseTarget_;
    XMVECTOR vFlyMove_;
    XMVECTOR vBaseAim_;
    XMFLOAT3 flyMove_;
    XMMATRIX matCamX_;
    XMMATRIX matCamY_;

    float moveTime_;
    float aimTime_;
    float flyTime_;
    float velocity_;
    float rotateSpeed_;
    float maxSpeed_;
    float wireLength_;
    float angleY_;
    float angleX_;
    float lockOnAngleLimit_;

    char status_;

    Particle* pParticle_;
    std::list<EnemyNormal*> enemyList_;


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

    //�L�������ǂ����蔲���Ȃ��悤�ɂ���
    void CharactorControll(XMVECTOR &moveVector);
    
    //�J�����̋����𐧌�
    void CameraMove(RayCastData ray);

    //�v���C���[�̃��C���[�A�N�V�������̃X�e�[�^�X��ݒ�
    void SetStatus(int type);
    
    //�Փ˔���
    void OnCollision(GameObject* pTarget) override;
    
    //�G�C���A�V�X�g
    bool IsAssistRange(XMVECTOR dirVec,XMFLOAT3 targetVec,float length=9999.0f);
    
    //�v���C���[�̃X�e�[�^�X�擾
    char GetSatatus() { return status_; }
    
    //�v���C���[�̈ړ��x�N�g���擾
    XMVECTOR GetPlayerMove() { return vPlayerMove_; }
    
    //�p�[�e�B�N��
    void OccurParticle();

    //�G���v���C���[�̔F�����X�g�ɓ����(�G�C���A�V�X�g�̑Ώۂ����炷����)
    void AddTargetList(EnemyNormal* target);

    //�G���v���C���[�̔F�����X�g����O��
    void DeleteTargetList(EnemyNormal* target);
    //�J��
    void Release() override;


};

