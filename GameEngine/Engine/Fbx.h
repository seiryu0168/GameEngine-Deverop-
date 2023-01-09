#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include"Direct3D.h"
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class Texture;

struct RayCastData
{
	XMFLOAT3 start;
	XMFLOAT3 dir;
	float dist;
	XMVECTOR hitPos;
	XMVECTOR normal;
	BOOL hit;
	float distLimit;

	RayCastData():start(XMFLOAT3(0,0,0)),
		dir(XMFLOAT3(0,0,0)),
		dist(9999.0f),
		hit(false),
		hitPos(XMVectorSet(0,0,0,0)),
		normal(XMVectorSet(0,0,0,0)),
		distLimit(9999.0f) {}
};

	 class FbxParts;
class Fbx
{
	
	////�}�e���A��
	////����
	//struct MATERIAL
	//{
	//	Texture* pTexture;    //�e�N�X�`��
	//	Texture* pNormalMap;  //�m�[�}���}�b�v
	//	XMFLOAT4 diffuse;	  //�f�B�t���[�Y(�}�e���A���̐F)
	//	XMFLOAT4 ambient;	  //�A���r�G���g
	//	XMFLOAT4 speculer;    //�X�y�L�����[(�c���c����\������z)
	//	float shininess;	  //�n�C���C�g�̋���
	//};

	////�V�F�[�_�[�ɑ�������܂Ƃ߂��\����
	//struct CONSTANT_BUFFER
	//{
	//	XMMATRIX matWVP;			//���[���h�A�r���[�A�v���W�F�N�V�����s��̍���(���_�ϊ��Ɏg��)
	//	XMMATRIX matW;				//���[���h�s��
	//	XMMATRIX matNormal;			//��]�s��Ɗg��s��̍���(�@���̕ό`�Ɏg��)
	//	XMFLOAT4 diffuseColor;		//�f�B�t���[�Y(�}�e���A���̐F)
	//	XMFLOAT4 ambient;			//�A���r�G���g
	//	XMFLOAT4 speculer;			//�X�y�L�����[
	//	XMFLOAT4 lightDirection;	//���C�g�̌���
	//	XMFLOAT4 cameraPosition;	//�J�����̈ʒu
	//	FLOAT	 shininess;			//�n�C���C�g�̋���
	//	BOOL	 isTexture;			//�e�N�X�`�����\���Ă��邩�ǂ���
	//	BOOL     isNormal;	//�m�[�}���}�b�v�����邩�ǂ���
	//	XMFLOAT4 customColor;       //�v���O�������ŐF��ς������ꍇ
	//};

	////���_�Ɋi�[�������
	////maya����fbx�o�͂��鎞�ɒ��_�@���̐ݒ�����Ȃ��ƕ\�������������Ȃ�
	////blender�̏ꍇ�͎����X���[�Y��؂�Ɛ������\�������
	//struct VERTEX
	//{
	//	XMVECTOR position;
	//	XMVECTOR uv;
	//	XMVECTOR normal;//blender�ł̓X���[�Y�V�F�[�h�ɂ�����Ńm�[�}���̎����X���[�Y��؂�Ȃ��Ɩ@���̃f�[�^�����������Ȃ��Đ������\������Ȃ�
	//	XMVECTOR tangent;//�ڐ�
	//};

	std::vector<FbxParts*> parts_;
	int vertexCount_;		//���_��
	int polygonCount_;		//�|���S����
	int materialCount_;		//�}�e���A����

	FbxManager* pFbxManager_;
	FbxScene* pFbxScene_;
	FbxTime::EMode frameRate_;
	float animSpeed_;
	int startFrame_;
	int endFrame_;

	//ID3D11Buffer* pVertexBuffer_; //���_�o�b�t�@
	//ID3D11Buffer** pIndexBuffer_;//�C���f�b�N�X�o�b�t�@
	//ID3D11Buffer* pConstantBuffer_;//�R���X�^���g�o�b�t�@
	//
	//MATERIAL* pMaterialList_;//�}�e���A�����X�g
	//int* indexCount_;
	//int** ppIndex_;
	//VERTEX* pVertices_;

	HRESULT CheckNode(FbxNode* pNode, std::vector<FbxParts*>* pPartsList);
public:

	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	/*HRESULT InitVertex(fbxsdk::FbxMesh*mesh);
	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);
	HRESULT CreateConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);*/
	void RayCast(RayCastData& ray,Transform& transform);
	

	//void ToPipeLine(Transform& transform);
	//void bufferSet();
	void    Draw(Transform& transform, SHADER_TYPE shaderType,int frame);
	void    Release();
};