#pragma once
#include"Direct3D.h"
#include"Texture.h"
#include"Transform.h"
#include"SAFE_DELETE_RELEASE.h"

class Sprite
{
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matPosition;
	};
protected:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	DWORD vertexNum_;
	VERTEX* vertices_;
	DWORD indexNum_;
	int* index_;
	
	XMUINT2 imgSize_;
	int hPict_;
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT Load(std::string fileName);

	void ToPipeLine(DirectX::XMMATRIX worldMatrix);
	void bufferSet();
	void Release();

public:
	Sprite();
	~Sprite();
	virtual HRESULT Initialize();
	virtual void InitVertex();
	virtual void InitIndex();
	void SetSize(UINT width, UINT height) { imgSize_ = { width,height }; }
	void SetSize(XMUINT2 size) { imgSize_ = size; }

	void Draw(Transform& transform);
};

