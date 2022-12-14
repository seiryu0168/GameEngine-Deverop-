#pragma once
#include"Engine/Direct3D.h"
#include"Engine/Texture.h"
#include"DirectXMath.h"
//#include"Engine/BillBoard.h"
#include<list>



class LineParticle
{
	enum LineMode
	{
		DEFAULT=0,
		BILLBOARD,
	};

private:
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMFLOAT4	color;
	};

	//���_���
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 uv;
	};

	float WIDTH_;//���C���p�[�e�B�N���̕�
	int LENGTH_;//���C���p�[�e�B�N���̃|�W�V�������L�������

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	Texture* pTexture_;
	std::list<XMFLOAT3> positionList_;
public:
	LineParticle();
	LineParticle(float width,int length);
	//���݈ʒu���L�� : pos
	void AddPosition(XMFLOAT3 pos);

	HRESULT Load(std::string fileName);
	void Draw(XMMATRIX matW = XMMatrixIdentity());
	void SetLineParameter(float width, int length);
	void DeleteLine();
	void Release();



};

