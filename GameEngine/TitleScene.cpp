#include "TitleScene.h"
#include"Engine/Model.h"
#include"Engine/Fbx.h"
#include"Player.h"
#include"Enemy_normal.h"
#include"Test.h"
#include"Stage1.h"

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//������
void TitleScene::Initialize()
{
	Instantiate<Stage1>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy_normal>(this);
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