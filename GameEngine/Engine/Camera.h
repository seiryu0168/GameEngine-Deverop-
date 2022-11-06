#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize(float width, float height);

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target);

	//�J�����̏�����x�N�g����ݒ�
	void SetUpVector(XMVECTOR upVector);

	//���_(������ʒu)���擾
	XMFLOAT3 GetPosition();

	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�r���{�[�h�p��]�s��
	XMMATRIX GetBillBoardMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();

};