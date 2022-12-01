#pragma once
#include"Enemy.h"
#include"Player.h"

class EnemyNormal : public Enemy
{
private:
    int hModel_;
    int life_;

    XMMATRIX matX_;
    XMMATRIX matY_; 
    bool visibleFlag_;

    XMVECTOR toPlayerVec_;
    XMVECTOR frontVec_;
    XMVECTOR upVec_;
    XMVECTOR vPosition_;
    Player* pPlayer_;

public:
    //�R���X�g���N�^
    EnemyNormal(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyNormal();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    void FixedUpdate() override;
    //�`��
    void Draw() override;

    //�G�l�~�[�̓���
    //���������x�N�g��
    void EnemyMove(XMVECTOR toVec);
    
    //���E���Ƀv���C���[�����邩�ǂ���
    //�G�l�~�[�̑O�����x�N�g���A�^�[�Q�b�g�̍��W�A����A���m����
    bool IsVisible(XMVECTOR vFront, XMVECTOR vTarget,float visibleAngle,float range);

    XMVECTOR GetToPlayerVector();

    //�J��
    void Release() override;

    //�Փ�
    void OnCollision(GameObject* pTarget) override;
};