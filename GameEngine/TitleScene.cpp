#include "TitleScene.h"
#include"Engine/Model.h"
#include"Engine/Fbx.h"
#include"Player.h"
#include"EnemyNormal.h"
#include"SetObject.h"
#include"Test.h"
#include"Stage1.h"
#include"StateList.h"

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//������
void TitleScene::Initialize()
{
	//�I�u�W�F�N�g�ݒu����N���X�����A���̃N���X�̒��Ŋe�I�u�W�F�N�g�𐶐�����
	//�������ɂ����̃N���X��e�ɐݒ肷���OK
	//�I�u�W�F�N�g�ݒu�N���X�ŃG�l�~�[�̃p�����[�^��ݒ肷��悤�ɂ���
	
	//feild���Ė��O�ɂ��Ƃ����ق�������
	//Instantiate<SetObject>(this);
	State::StateCreate();
	Instantiate<Stage1>(this);
	Instantiate<Player>(this);
	for (int i = 0; i < 11; i++)
	{
		Instantiate<EnemyNormal>(this);
	}
	Instantiate<Test>(this);
}

//�X�V
void TitleScene::Update()
{
	
}

void TitleScene::FixedUpdate()
{

}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}