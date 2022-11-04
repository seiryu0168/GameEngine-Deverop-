#include <d3dcompiler.h>
#include "Direct3D.h"
#include<array>

//�ϐ�
namespace Direct3D
{
	ID3D11Device* pDevice;						//�f�o�C�X
	ID3D11DeviceContext* pContext;				//�f�o�C�X�R���e�L�X�g
	IDXGISwapChain* pSwapChain;					//�X���b�v�`�F�C��
	ID3D11RenderTargetView* pRenderTargetView;	//�����_�[�^�[�Q�b�g�r���[
	ID3D11BlendState* pBlendState;				//�u�����h�X�e�[�g
	ID3D11Texture2D* pDepthStencil;				//�[�x�X�e���V��
	ID3D11DepthStencilView* pDepthStencilView;	//�[�x�X�e���V���r���[
	//ID3D11ShaderResourceView* pSRV[2];				//�V�F�[�_�[���\�[�X�r���[
	//ID3D11Texture2D* pRenderTarget;


	struct SHADER_BUNDLE
	{
		ID3D11VertexShader* pVertexShader = nullptr;	//���_�V�F�[�_�[
		ID3D11PixelShader* pPixelShader = nullptr;		//�s�N�Z���V�F�[�_�[
		ID3D11InputLayout* pVertexLayout = nullptr;	//���_�C���v�b�g���C�A�E�g
		ID3D11RasterizerState* pRasterizerState = nullptr;	//���X�^���C�U�[
	};
	SHADER_BUNDLE shaderBundle[SHADER_MAX];

	int screenWidth;
	int screenHeight;
}

//������
HRESULT Direct3D::Initialize(int winW, int winH, HWND hWnd)
{

	screenWidth = winW;
	screenHeight = winH;
	///////////////////////////���낢�돀�����邽�߂̐ݒ�///////////////////////////////
	//���낢��Ȑݒ荀�ڂ��܂Ƃ߂��\����
	DXGI_SWAP_CHAIN_DESC scDesc;

	//�Ƃ肠�����S��0
	ZeroMemory(&scDesc, sizeof(scDesc));

	//�`���̃t�H�[�}�b�g
	scDesc.BufferDesc.Width = winW;		//��ʕ�
	scDesc.BufferDesc.Height = winH;	//��ʍ���
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

	//FPS�i1/60�b��1��j
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//���̑�
	scDesc.Windowed = TRUE;			//�E�B���h�E���[�h���t���X�N���[����
	scDesc.OutputWindow = hWnd;		//�E�B���h�E�n���h��
	scDesc.BufferCount = 1;			//�o�b�N�o�b�t�@�̖���
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�o�b�N�o�b�t�@�̎g��������ʂɕ`�悷�邽�߂�
	scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
	scDesc.SampleDesc.Quality = 0;		//�@�V

	////////////////��L�ݒ�����ƂɃf�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C�����쐬////////////////////////
	D3D_FEATURE_LEVEL level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,						// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
		D3D_DRIVER_TYPE_HARDWARE,		// �h���C�o�̃^�C�v��n���B�ӂ���HARDWARE
		nullptr,						// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵�Ȃ�������nullptr
		0,								// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
		nullptr,						// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ���OK
		0,								// ��̈����Ń��x�������w�肵����
		D3D11_SDK_VERSION,				// SDK�̃o�[�W�����B�K�����̒l
		&scDesc,						// ��ł��낢��ݒ肵���\����
		&pSwapChain,					// ������������SwapChain�̃A�h���X���Ԃ��Ă���
		&pDevice,						// ������������Device�A�h���X���Ԃ��Ă���
		&level,							// ������������Device�AContext�̃��x�����Ԃ��Ă���
		&pContext);						// ������������Context�̃A�h���X���Ԃ��Ă���

	///////////////////////////�����_�[�^�[�Q�b�g�r���[�쐬///////////////////////////////
	//�X���b�v�`�F�[������o�b�N�o�b�t�@���擾�i�o�b�N�o�b�t�@ �� �����_�[�^�[�Q�b�g�j

	//�����_�[�^�[�Q�b�g�r���[���쐬
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	/*D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceView;
	ShaderResourceView.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ShaderResourceView.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	ShaderResourceView.Texture2D.MipLevels = 1;
	Direct3D::pDevice->CreateShaderResourceView(pBackBuffer, &ShaderResourceView, &pSRV[0]);
	�����p�̃����_�[�^�[�Q�b�g�A�����_�[�^�[�Q�b�g�r���[�A�V�F�[�_�[���\�[�X�r���[�쐬
	D3D11_TEXTURE2D_DESC rtDesc;
	ZeroMemory(&rtDesc, sizeof(rtDesc));
	rtDesc.Width = winW;
	rtDesc.Height = winH;
	rtDesc.MipLevels = 1;
	rtDesc.ArraySize = 1;
	rtDesc.Format = DXGI_FORMAT_D32_FLOAT;
	rtDesc.SampleDesc.Count = 1;
	rtDesc.SampleDesc.Quality = 0;
	rtDesc.Usage = D3D11_USAGE_DEFAULT;
	rtDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	rtDesc.CPUAccessFlags = 0;
	rtDesc.MiscFlags = 0;
	Direct3D::pDevice->CreateTexture2D(&rtDesc, NULL, &pRenderTarget);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�����_�[�^�[�Q�b�g�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	Direct3D::pDevice->CreateShaderResourceView(pRenderTarget, &srv, &pSRV[1]);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	RenderTarget* pRenderTarget = new RenderTarget[4];

	for (int i = 0; i < RENDER_TARGET_MAX; i++)
	{
		pRenderTarget[i].Init(targetList[i], winW, winH);
		renderTargetList_.push_back(&pRenderTarget[i]);
	}*/

	//�u�����h�X�e�[�g�̍쐬
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr;
	hr=pDevice->CreateBlendState(&desc, &pBlendState);
	if(FAILED(hr))
	{
		MessageBox(nullptr, L"�u�����h�X�e�[�g�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	
	//�ꎞ�I�Ƀo�b�N�o�b�t�@���擾���������Ȃ̂ŉ��
	SAFE_RELEASE(pBackBuffer);

	///////////////////////////�r���[�|�[�g�i�`��͈́j�ݒ�///////////////////////////////
	//�����_�����O���ʂ�\������͈�
	D3D11_VIEWPORT vp;
	vp.Width = (float)winW;	//��
	vp.Height = (float)winH;//����
	vp.MinDepth = 0.0f;	//��O
	vp.MaxDepth = 1.0f;	//��
	vp.TopLeftX = 0;	//��
	vp.TopLeftY = 0;	//��


	//�[�x�X�e���V���r���[�̍쐬
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = winW;
	descDepth.Height = winH;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	pDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	pDevice->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);

	//�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�i�p�C�v���C���j
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);       //�f�[�^�̓��͎�ނ��w��
	pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);        // �`����ݒ�
	pContext->RSSetViewports(1, &vp);

	//�V�F�[�_�[����
	 hr=InitShader();
	 if (FAILED(hr))
	 {
		 return hr;
	 }

	 return S_OK;
}

//�V�F�[�_�[����
HRESULT Direct3D::InitShader()
{
	if (FAILED(InitShader2D()))
	{
		return E_FAIL;
	}
	if (FAILED(InitShader3D()))
	{
		return E_FAIL;
	}
	if(FAILED(InitShaderEFF()))
	{
		return E_FAIL;

	}
	return S_OK;

}

HRESULT Direct3D::InitShader2D()
{
	HRESULT hr;
	// ���_�V�F�[�_�̍쐬�i�R���p�C���j
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"���_�V�F�[�_�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	//���_�C���v�b�g���C�A�E�g   ���_�V�F�[�_�\�ɓn�����
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�ʒu
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(XMVECTOR),  D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV���W
	};
	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_2D].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"���_�C���v�b�g���C�A�E�g�̐ݒ�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pPixelShader);

	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompilePS);
		MessageBox(nullptr, L"�s�N�Z���V�F�[�_�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompilePS);

	//���X�^���C�U�쐬
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[SHADER_2D].pRasterizerState);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompilePS);
		MessageBox(nullptr, L"�s�N�Z���V�F�[�_�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShader3D()
{
	HRESULT hr;
	// ���_�V�F�[�_�̍쐬�i�R���p�C���j
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"���_�V�F�[�_�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////���_�C���v�b�g���C�A�E�g///////////////////////////////////////////////
	//HLSL(�V�F�[�_�[�̎�)�ɑ�����̎�ނƂ��̐ݒ���s��
	//1.�Z�}���e�B�b�N�̖��O
	//2.�Z�}���e�B�b�N�C���f�b�N�X(�����Z�}���e�B�b�N�����v�f����������Ƃ��Ɏg��)
	//3.�v�f�f�[�^�̃f�[�^�f�[�^�^
	//4.���̓A�Z���u�������ʂ��鐮���l(0�`15)
	//5.���_�̐擪�A�h���X����̃I�t�Z�b�g(�o�C�g�P��)
	//6.���̓X���b�g�̓��̓f�[�^�N���X�̎���
	//7.�o�b�t�@����1�v�f�i�ޑO�ɁA�����C���X�^���X���Ƃ̃f�[�^���g�p����
	//�`�悷��C���X�^���X�̐����_�P�ʂ̃f�[�^���܂ޗv�f�̏ꍇ�A0�ɂ���E�E�E�炵��
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�ʒu
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(XMVECTOR),  D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV���W
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },  //�@��
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_3D].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"���_�C���v�b�g���C�A�E�g�̐ݒ�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�s�N�Z���V�F�[�_�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	//���X�^���C�U�쐬
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[SHADER_3D].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���X�^���C�U�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	return S_OK;
}

HRESULT Direct3D::InitShaderEFF()
{
	HRESULT hr;
	// ���_�V�F�[�_�̍쐬�i�R���p�C���j
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"BillBoard.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_EFF].pVertexShader);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"���_�V�F�[�_�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"BillBoard.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_EFF].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�s�N�Z���V�F�[�_�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	//////////////////////////////////////////////////���_�C���v�b�g���C�A�E�g///////////////////////////////////////////////
	//HLSL(�V�F�[�_�[�̎�)�ɑ�����̎�ނƂ��̐ݒ���s��
	//1.�Z�}���e�B�b�N�̖��O
	//2.�Z�}���e�B�b�N�C���f�b�N�X(�����Z�}���e�B�b�N�����v�f����������Ƃ��Ɏg��)
	//3.�v�f�f�[�^�̃f�[�^�f�[�^�^
	//4.���̓A�Z���u�������ʂ��鐮���l(0�`15)
	//5.���_�̐擪�A�h���X����̃I�t�Z�b�g(�o�C�g�P��)
	//6.���̓X���b�g�̓��̓f�[�^�N���X�̎���
	//7.�o�b�t�@����1�v�f�i�ޑO�ɁA�����C���X�^���X���Ƃ̃f�[�^���g�p����
	//�`�悷��C���X�^���X�̐����_�P�ʂ̃f�[�^���܂ޗv�f�̏ꍇ�A0�ɂ���E�E�E�炵��
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,					D3D11_INPUT_PER_VERTEX_DATA, 0 },  //�ʒu
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	  0, sizeof(XMVECTOR),  D3D11_INPUT_PER_VERTEX_DATA, 0 },  //UV���W
	};

	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_EFF].pVertexLayout);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pCompileVS);
		MessageBox(nullptr, L"���_�C���v�b�g���C�A�E�g�̐ݒ�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);


	//���X�^���C�U�쐬
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise =TRUE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[SHADER_EFF].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���X�^���C�U�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	return S_OK;
}
void Direct3D::SetShader(SHADER_TYPE type)
{
	//���ꂼ����f�o�C�X�R���e�L�X�g�ɃZ�b�g  �����̏����g���ĕ`����s��
	pContext->VSSetShader(shaderBundle[type].pVertexShader, NULL, 0);	//���_�V�F�[�_�[
	pContext->PSSetShader(shaderBundle[type].pPixelShader, NULL, 0);	//�s�N�Z���V�F�[�_�[
	pContext->IASetInputLayout(shaderBundle[type].pVertexLayout);	//���_�C���v�b�g���C�A�E�g
	pContext->RSSetState(shaderBundle[type].pRasterizerState);		//���X�^���C�U�[
}
//�`��J�n
void Direct3D::BeginDraw()
{
	//��ʂ��N���A
		//�w�i�F
		float clearColor[4] = { 0.1,0.5,0.5,1.0 };
		//�����_�[�^�[�Q�b�g�r���[���N���A
		pContext->ClearRenderTargetView(pRenderTargetView, clearColor);

	//�[�x�o�b�t�@�N���A
	pContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//�`��I��
void Direct3D::EndDraw()
{
	//�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
	pSwapChain->Present(0, 0);
}

//�������
void Direct3D::Release()
{
	//�������
	for (int releaseShader = 0; releaseShader < SHADER_MAX; releaseShader++)
	{
		SAFE_RELEASE(shaderBundle[releaseShader].pRasterizerState);
		SAFE_RELEASE(shaderBundle[releaseShader].pVertexLayout);
		SAFE_RELEASE(shaderBundle[releaseShader].pPixelShader);
		SAFE_RELEASE(shaderBundle[releaseShader].pVertexShader);
	}
	SAFE_RELEASE(pDepthStencilView);				//�[�x�X�e���V���r���[
	SAFE_RELEASE(pDepthStencil);					//�[�x�X�e���V��
	SAFE_RELEASE(pBlendState);
	SAFE_RELEASE(pRenderTargetView);
	SAFE_RELEASE(pSwapChain);		//�X���b�v�`�F�C��
	SAFE_RELEASE(pContext);			//�f�o�C�X�R���e�L�X�g
	SAFE_RELEASE(pDevice);			//�f�o�C�X
}


ID3D11BlendState* Direct3D::GetBlendState()
{
	return pBlendState;
}

//void Direct3D::SetRenderTargetView(int renderTarget)
//{
//	pContext->OMSetRenderTargets(1, &pRenderTargetView[renderTarget], pDepthStencilView);
//}
//RenderTarget::RenderTarget()
//	:pLayerBuffer(nullptr),pRenderTargetView(nullptr),pShaderResourceView(nullptr)
//{
//
//}
//RenderTarget::~RenderTarget()
//{
//	SAFE_DELETE(pShaderResourceView);
//	SAFE_DELETE(pRenderTargetView);
//	SAFE_DELETE(pLayerBuffer);
//}
//
//HRESULT RenderTarget::Init(int renderType,int winW,int winH)
//{
//	HRESULT hr;
//	switch(renderType)
//	{
//	case BACK_BUFFER:
//	
//		Direct3D::pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pLayerBuffer);
//		Direct3D::pDevice->CreateRenderTargetView(pLayerBuffer, NULL, &pRenderTargetView);
//		break;
//	
//	case RENDER_TARGET:
//		D3D11_TEXTURE2D_DESC rtDesc;
//		ZeroMemory(&rtDesc, sizeof(rtDesc));
//		rtDesc.Width = winW;
//		rtDesc.Height = winH;
//		rtDesc.MipLevels = 1;
//		rtDesc.ArraySize = 1;
//		rtDesc.Format = DXGI_FORMAT_D32_FLOAT;
//		rtDesc.SampleDesc.Count = 1;
//		rtDesc.SampleDesc.Quality = 0;
//		rtDesc.Usage = D3D11_USAGE_DEFAULT;
//		rtDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//		rtDesc.CPUAccessFlags = 0;
//		rtDesc.MiscFlags = 0;
//		hr = Direct3D::pDevice->CreateTexture2D(&rtDesc, NULL, &pLayerBuffer);
//		if (FAILED(hr))
//		{
//			MessageBox(nullptr, L"�����_�[�^�[�Q�b�g�̍쐬�Ɏ��s",L"�G���[", MB_OK);
//			return hr;
//		}
//
//		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
//		ZeroMemory(&rtvDesc, sizeof(rtvDesc));
//		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
//
//		hr = Direct3D::pDevice->CreateRenderTargetView(pLayerBuffer, &rtvDesc, &pRenderTargetView);
//		if (FAILED(hr))
//		{
//			MessageBox(nullptr, L"�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s", L"�G���[", MB_OK);
//			return hr;
//		}
//		D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
//		srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//		srv.Texture2D.MipLevels = 1;
//		hr = Direct3D::pDevice->CreateShaderResourceView(pLayerBuffer, &srv, &pShaderResourceView);
//		if (FAILED(hr))
//		{
//			MessageBox(nullptr, L"�V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s", L"�G���[", MB_OK);
//			return hr;
//		}
//		return S_OK;
//	}
//
//	
//}
//void RenderTarget::SetShaderResource()
//{
//}
//void RenderTarget::SetRenderTarget()
//{
//	Direct3D::pContext->OMSetRenderTargets(1, &pRenderTargetView, Direct3D::pDepthStencilView);
//}
//void RenderTarget::ClearRenderTarget()
//{
//	//�w�i�F
//	float clearColor[4]={ 0.5,0.5,0.5,1.0 };
//	//�����_�[�^�[�Q�b�g�r���[���N���A
//	Direct3D::pContext->ClearRenderTargetView(pRenderTargetView, clearColor);
//}
//ID3D11ShaderResourceView** RenderTarget::GetSRV()
//{
//	return &pShaderResourceView;
//}
//
//void RenderTarget::Release()
//{
//	SAFE_DELETE(pShaderResourceView);
//	SAFE_DELETE(pRenderTargetView);
//	SAFE_DELETE(pLayerBuffer);
//}