#include "LineParticle.h"
#include"Engine/Camera.h"
LineParticle::LineParticle()
	:WIDTH_(0.5),
	LENGTH_(30),
	pVertexBuffer_(nullptr),
	pConstantBuffer_(nullptr),
	pTexture_(nullptr)
{
	
}

//���݈ʒu���L�� : pos
void LineParticle::AddPosition(XMFLOAT3 pos)
{
	//���X�g�̐�[�Ɍ��݈ʒu������
	positionList_.push_front(pos);
	
	//LENGTH�����Ă���I�[��position���폜
	if (positionList_.size() > LENGTH_)
	{
		positionList_.pop_back();
	}

	//���_�o�b�t�@���
	SAFE_RELEASE(pVertexBuffer_);

	//�J�����̈ʒu�擾(�x�N�g����)
	XMFLOAT3 camPos = Camera::GetPosition();
	XMVECTOR vCamPos = XMLoadFloat3(&camPos);

	//���_�f�[�^�쐬
	VERTEX* vertices = new VERTEX[LENGTH_ * 2];
	int index = 0;

	auto itr = positionList_.begin();
	for (int i = 0; i < LENGTH_; i++)
	{
		//�L�����Ă���ʒu�擾
		XMVECTOR vPos = XMLoadFloat3(&(*itr));

		itr++;
		if (itr == positionList_.end())
		{
			break;
		}

		//�������擾�����ʒu���玟�̈ʒu�Ɍ������x�N�g��
		XMVECTOR vLine = XMLoadFloat3(&(*itr)) - vPos;

		XMVECTOR vArm = XMVector3Cross(vLine, vCamPos);
		vArm = XMVector3Normalize(vArm)*WIDTH_;

		XMFLOAT3 pos;
		XMStoreFloat3(&pos, vPos + vArm);

		VERTEX vertex1 = { pos,XMFLOAT3((float)i / LENGTH_,0,0) };

		XMStoreFloat3(&pos, vPos - vArm);

		VERTEX vertex2 = { pos,XMFLOAT3((float)i / LENGTH_,1,0) };

		int s = sizeof(VERTEX);

		vertices[index] = vertex1;
		index++;
		vertices[index] = vertex2;
		index++;
	}
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * LENGTH_ * 2;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);

	delete[] vertices;
}

HRESULT LineParticle::Load(std::string fileName)
{
	D3D11_BUFFER_DESC bd_constant;
	bd_constant.ByteWidth = sizeof(CONSTANT_BUFFER);
	bd_constant.Usage = D3D11_USAGE_DYNAMIC;
	bd_constant.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd_constant.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd_constant.MiscFlags = 0;
	bd_constant.StructureByteStride = 0;

	Direct3D::pDevice->CreateBuffer(&bd_constant, nullptr, &pConstantBuffer_);
	pTexture_ = new Texture;
	wchar_t name[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, name, fileName.c_str(), fileName.length());

	HRESULT hr = pTexture_->Load(name);
	if (FALSE(hr))
	{
		MessageBox(nullptr, L"���C���p�[�e�B�N���̃e�N�X�`���̃��[�h�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;


}

void LineParticle::Draw()
{
	Direct3D::SetShader(SHADER_EFF);
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.color = XMFLOAT4(1, 1, 1, 1);

	D3D11_MAPPED_SUBRESOURCE pdata;

	//GPU����̃f�[�^�A�N�Z�X���~�߂�
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	
	errno_t res;
	//�f�[�^�𑗂�
	res = memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
	
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	//�f�[�^�A�N�Z�X�ĊJ
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	//���_�o�b�t�@
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);//���_�V�F�[�_�[�p
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);//�s�N�Z���V�F�[�_�[�p

	//���_�̕��ѕ����w��
	Direct3D::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	Direct3D::pContext->Draw(positionList_.size() - 1 * 2, 0);

	Direct3D::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void LineParticle::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	positionList_.clear();
}
