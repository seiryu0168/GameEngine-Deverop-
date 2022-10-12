//#pragma once
//#include <d3d11.h>
//#include <fbxsdk.h>
//#Include"Texture.h"
//#include<DirectXMath.h>
//#include"Transform.h"
//class FbxParts
//{
//
//	//�}�e���A��
////����
//	struct MATERIAL
//	{
//		Texture* pTexture;    //�e�N�X�`��
//		XMFLOAT4 diffuse;	  //�f�B�t���[�Y(�}�e���A���̐F)
//		XMFLOAT4 ambient;	  //�A���r�G���g
//		XMFLOAT4 speculer;    //�X�y�L�����[(�c���c����\������z)
//		float shininess;	  //�n�C���C�g�̋���
//
//	};
//
//	//�V�F�[�_�[�ɑ�������܂Ƃ߂��\����
//	struct CONSTANT_BUFFER
//	{
//		XMMATRIX matWVP;			//���[���h�A�r���[�A�v���W�F�N�V�����s��̍���(���_�ϊ��Ɏg��)
//		XMMATRIX matW;				//���[���h�s��
//		XMMATRIX matNormal;			//��]�s��Ɗg��s��̍���(�@���̕ό`�Ɏg��)
//		XMFLOAT4 diffuseColor;		//�f�B�t���[�Y(�}�e���A���̐F)
//		XMFLOAT4 ambient;			//�A���r�G���g
//		XMFLOAT4 speculer;			//�X�y�L�����[
//		XMFLOAT4 lightDirection;	//���C�g�̌���
//		XMFLOAT4 cameraPosition;	//�J�����̈ʒu
//		FLOAT	 shininess;			//�n�C���C�g�̋���
//		BOOL	 isTexture;			//�e�N�X�`��
//	};
//
//	//���_�Ɋi�[�������
//	//maya����fbx�o�͂��鎞�ɒ��_�@���̐ݒ�����Ȃ��ƕ\�������������Ȃ�
//	//blender�̏ꍇ�͎����X���[�Y��؂�Ɛ������\�������
//	struct VERTEX
//	{
//		XMVECTOR position;
//		XMVECTOR uv;
//		XMVECTOR normal;//blender�ł̓X���[�Y�V�F�[�h�ɂ�����Ńm�[�}���̎����X���[�Y��؂�Ȃ��Ɩ@���̃f�[�^�����������Ȃ��Đ������\������Ȃ�
//	};
//
//	int vertexCount_;		//���_��
//	int polygonCount_;		//�|���S����
//	int materialCount_;		//�}�e���A����
//
//	ID3D11Buffer* pVertexBuffer_;
//	ID3D11Buffer** pIndexBuffer_;
//	ID3D11Buffer* pConstantBuffer_;
//	MATERIAL* pMaterialList_;
//	int* indexCount_;
//
//	int** ppIndex_;
//	VERTEX* pVertices_;
//
//public:
//
//	Fbx();
//	~Fbx();
//	HRESULT Load(std::string fileName);
//	HRESULT InitVertex(fbxsdk::FbxMesh* mesh);
//	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);
//	HRESULT CreateConstantBuffer();
//	void InitMaterial(fbxsdk::FbxNode* pNode);
//	void RayCast(RayCastData& ray, Transform& transform);
//
//
//	//void ToPipeLine(Transform& transform);
//	//void bufferSet();
//	void    Draw(Transform& transform, SHADER_TYPE shaderType);
//	void    Release();
//};
//
