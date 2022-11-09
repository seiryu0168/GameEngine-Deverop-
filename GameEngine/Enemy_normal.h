#pragma once
#include"Enemy.h"
#include"Player.h"

class Enemy_normal : public Enemy
{
private:
    int hModel_;

    XMMATRIX matX_;
    XMMATRIX matY_; 
    bool visibleFlag_;
    

    XMVECTOR frontVec_;
    XMVECTOR upVec_;
    XMVECTOR vPosition_;
    Player* pPlayer_;
public:
    //�R���X�g���N�^
    Enemy_normal(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy_normal();

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

    //�J��
    void Release() override;
};