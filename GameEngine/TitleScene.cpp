#include "TitleScene.h"
#include"Player.h"
#include"Engine/Model.h"
#include"Test.h"
#include"Engine/Fbx.h"
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//������
void TitleScene::Initialize()
{
	Instantiate<Test>(this);
	Instantiate<Player>(this);
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