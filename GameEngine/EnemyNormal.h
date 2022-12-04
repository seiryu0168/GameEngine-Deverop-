#pragma once
#include"Enemy.h"
#include"Player.h"

class EnemyNormal : public Enemy
{
private:
    bool     visibleFlag_;  //�v���C���[�������Ă��邩�ǂ���
    bool     isTargetList_; //�v���C���[�̃^�[�Q�b�g���X�g�ɓ����Ă邩�ǂ���
    int      hModel_;       //���f���ԍ�
    int      life_;         //�G�̗̑�

    XMMATRIX matX_;         //X���̉�]�s��
    XMMATRIX matY_;         //Y���̉�]�s��
    XMVECTOR toPlayerVec_;  //�v���C���[�Ɍ������x�N�g��
    XMVECTOR frontVec_;     //�O�����x�N�g��(���̃x�N�g������ɂ��Ď��E�����܂�)
    XMVECTOR upVec_;        //������x�N�g��(�v���C���[�Ƃ̈ʒu�֌W�����߂鎞�Ɏg�����肷��)
    XMVECTOR vPosition_;    //���݈ʒu�̃x�N�g��
    Player*  pPlayer_;      //�v���C���[�̃|�C���^

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

    //�v���C���[�֌������x�N�g���̎擾
    XMVECTOR GetToPlayerVector();

    //isTargetList�̃t���O�擾
    bool GetIsList() { return isTargetList_; }

    //�J��
    void Release() override;

    //�Փ�
    void OnCollision(GameObject* pTarget) override;
};