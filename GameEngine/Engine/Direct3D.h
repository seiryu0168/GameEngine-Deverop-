#pragma once
#include <d3d11.h>
#include<assert.h>
#include <DirectXMath.h>
#include<vector>
#include"SAFE_DELETE_RELEASE.h"
using namespace DirectX;

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum SHADER_TYPE
{
	SHADER_2D = 0,
	SHADER_3D,
	SHADER_EFF,
	SHADER_MAX,
};
enum TARGET
{
	TARGET_BACK_BUFFER=0,
	TARGET_RENDER_TARGET_1,
	TARGET_RENDER_TARGET_2,
	TARGET_RENDER_TARGET_3,
	TARGET_RENDER_TARGET_MAX
};

enum RENDER_TYPE
{
	BACK_BUFFER=0,
	RENDER_TARGET,
	RENDER_MAX
};

namespace Direct3D
{
	extern ID3D11Device* pDevice;				//�f�o�C�X
	extern ID3D11DeviceContext* pContext;		//�f�o�C�X�R���e�L�X�g
	/*std::vector<RenderTarget*> renderTargetList_;
	int targetList[] =
	{
		BACK_BUFFER,
		RENDER_TARGET,
		RENDER_TARGET,
		RENDER_TARGET,
	};*/

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
    HRESULT InitShader();
	HRESULT InitShader2D();
	HRESULT InitShader3D();
	HRESULT InitShaderEFF();

	ID3D11BlendState* GetBlendState();
	//void SetRenderTargetView(int renderTarget);
	void SetShader(SHADER_TYPE type);
	/*ID3D11ShaderResourceView** GetSRV(int srvNum);
	IDXGISwapChain* GetSwapChain();
	ID3D11DepthStencilView* GetDepthStencilView();*/

	//�`��J�n
	void BeginDraw();


	//�`��I��
	void EndDraw();

	//���
	void Release();

};

//class RenderTarget
//{
//private:
//	ID3D11Texture2D* pLayerBuffer;
//	ID3D11RenderTargetView* pRenderTargetView;
//	ID3D11ShaderResourceView* pShaderResourceView;
//public:
//	RenderTarget();
//	~RenderTarget();
//
//	HRESULT Init(int renderType,int winW,int winH);
//	void SetShaderResource();
//	void SetRenderTarget();
//	void ClearRenderTarget();
//	ID3D11ShaderResourceView** GetSRV();
//	void Release();
//};