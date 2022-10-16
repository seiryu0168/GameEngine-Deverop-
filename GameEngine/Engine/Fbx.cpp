#include "Fbx.h"
#include"Camera.h"
#include"Math.h"
#include"Texture.h"


Fbx::Fbx()
{
	vertexCount_ = 0;
	polygonCount_ = 0;
	materialCount_ = 0;
	pVertexBuffer_ = nullptr;
	pIndexBuffer_ = nullptr;
	pConstantBuffer_ = nullptr;
	pMaterialList_ = nullptr;
	indexCount_ = nullptr;	
}
Fbx::~Fbx()
{
	Release();
}

//FBX���[�h
HRESULT Fbx::Load(std::string fileName)
{
	//�}�l�[�W���𐶐�
	FbxManager* pFbxManager = FbxManager::Create();

	//�C���|�[�^�[�𐶐�
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//���b�V�������擾
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();


	//���݂̃J�����g�f�B���N�g����ޔ����Ă���
	WCHAR defaultDirectory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultDirectory);
	//fileName����f�B���N�g�����擾
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());
	WCHAR dir[MAX_PATH];
	_wsplitpath_s(wtext, nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);
	

	//�f�B���N�g���ύX
	SetCurrentDirectory(dir);
	
	//�e���̌����擾
	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
	polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount();//�}�e���A���̐�

	InitVertex(mesh);
	InitIndex(mesh);
	CreateConstantBuffer();
	InitMaterial(pNode);

	//�f�B���N�g�������ɖ߂�
	SetCurrentDirectory(defaultDirectory);

	//�}�l�[�W�����
	pFbxManager->Destroy();
	return S_OK;
}

///////////////////////////////////////////���_//////////////////////////////////////////
HRESULT Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//���_��������z��
	pVertices_ = new VERTEX[vertexCount_];

	//�S�|���S��
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3���_��
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//���ׂ钸�_�̔ԍ�
			int index = mesh->GetPolygonVertex(poly, vertex);

			//���_�̈ʒu
			FbxVector4 pos = mesh->GetControlPointAt(index);
			pVertices_[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//���_��UV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			pVertices_[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//���_�̖@��
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//���Ԗڂ̃|���S���́A���Ԗڂ̒��_�̖@�����Q�b�g
			pVertices_[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}
	}

	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = pVertices_;
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"���_�f�[�^�p�o�b�t�@�̐ݒ�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}

	return S_OK;
}

/////////////////////////////�C���f�b�N�X///////////////////////////////////
HRESULT Fbx::InitIndex(fbxsdk::FbxMesh* mesh)
{
	ppIndex_ = new int*[materialCount_];
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	indexCount_ = new int[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;
		ppIndex_[i] = new int[polygonCount_ * 3];
		//�S�|���S��
		for (DWORD poly = 0; poly < polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i)
			{
				//3���_��
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					ppIndex_[i][count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}
		indexCount_[i] = count;

		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = ppIndex_[i];
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s", L"�G���[", MB_OK);
			return hr;
		}
	}
	return S_OK;
}

//////////////////////////////////�R���X�^���g�o�b�t�@�쐬///////////////////////////////////	
HRESULT Fbx::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

void Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = new MATERIAL[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		//i�Ԗڂ̃}�e���A�������擾
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		//�t�H���V�F�[�f�B���O�ׂ̈Ƀ}�e���A���������o��
		FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;

		//�e�N�X�`�����
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//�󂯎��p�̊e�}�e���A���p�����[�^�̏�����
		FbxDouble3 diffuse = FbxDouble3(0, 0, 0);
		FbxDouble3 ambient = FbxDouble3(0, 0, 0);
		FbxDouble3 speculer = FbxDouble3(0, 0, 0);

		diffuse = pPhong->Diffuse;
		ambient = pPhong->Ambient;
		//diffuse��ambient������
		pMaterialList_[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
		pMaterialList_[i].ambient = XMFLOAT4((float)ambient[0], (float)ambient[1], (float)ambient[2], 1.0f);
		pMaterialList_[i].speculer = XMFLOAT4(0, 0, 0, 0);
		pMaterialList_[i].shininess = 0;
		
		//Phong�̃N���X�Ȃ̂�Lambert�̃N���X�Ȃ̂��𔻕�(Lambert���ƃX�y�L�����[�̒l�������Ȃ�)
		if (pPhong->GetClassId().Is(FbxSurfacePhong::ClassId))
		{
			speculer = pPhong->Specular;
			pMaterialList_[i].speculer = XMFLOAT4((float)speculer[0], (float)speculer[1], (float)speculer[2], 1.0f);
			//blender����1-�e���̒lx100�ɂ�����
			pMaterialList_[i].shininess = pPhong->Shininess;
		}

		//�e�N�X�`���̖���
		//pMaterialList_[i].pTexture = lProperty.GetSrcObjectCount<FbxFileTexture>();
		if(lProperty.GetSrcObjectCount<FbxFileTexture>()>0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//�p�X�����t�@�C�����Ɗg���q�����ɂ���
			char name[_MAX_FNAME];	//�t�@�C����
			char ext[_MAX_EXT];		//�g���q
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			sprintf_s(name, "%s%s", name, ext);

			wchar_t wtext[FILENAME_MAX];
			size_t ret;
			mbstowcs_s(&ret, wtext, name, strlen(name));

			//�t�@�C������e�N�X�`���쐬
			pMaterialList_[i].pTexture = new Texture;
			pMaterialList_[i].pTexture->Load(wtext);
		}

		//�e�N�X�`������
		else
		{
			pMaterialList_[i].pTexture = nullptr;
			//�}�e���A���̐F
			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			FbxDouble3  diffuse = pMaterial->Diffuse;
			pMaterialList_[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
		}
	}
}

void Fbx::Draw(Transform& transform, SHADER_TYPE shaderType)
{
	transform.Calclation();
	float factor[4] = { D3D11_BLEND_ZERO,D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };

	//�R���X�^���g�o�b�t�@�ɏ���n��
	for (int i = 0; i < materialCount_; i++)
	{
		Direct3D::SetShader(shaderType);
		CONSTANT_BUFFER cb;
		cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
		cb.matW = XMMatrixTranspose(transform.GetWorldMatrix());
		cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());
		cb.lightDirection = XMFLOAT4(0, 1, 0, 0);
		cb.cameraPosition = XMFLOAT4(Camera::GetPosition().x, Camera::GetPosition().y, Camera::GetPosition().z, 0);

		cb.isTexture = pMaterialList_[i].pTexture != nullptr;
		cb.diffuseColor = pMaterialList_[i].diffuse;
		cb.ambient = pMaterialList_[i].ambient;
		cb.speculer = pMaterialList_[i].speculer;
		cb.shininess = pMaterialList_[i].shininess;

			D3D11_MAPPED_SUBRESOURCE pdata;
			Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);			//GPU����̃f�[�^�A�N�Z�X���~�߂�
			memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));							//�f�[�^��l�𑗂�
		if (cb.isTexture)
		{

			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
			ID3D11ShaderResourceView* pSRV1 = pMaterialList_[i].pTexture->GetSRV();

			Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV1);


		}
			Direct3D::pContext->Unmap(pConstantBuffer_, 0);//�ĊJ
			Direct3D::pContext->OMSetBlendState(Direct3D::GetBlendState(), factor, 0xffffffff);			//�u�����h�X�e�[�g
			//���_�o�b�t�@
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

			// �C���f�b�N�X�o�b�t�@�[���Z�b�g
			stride = sizeof(int);
			offset = 0;
			Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);
			
			//�R���X�^���g�o�b�t�@
			Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);							//���_�V�F�[�_�[�p	
			Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);							//�s�N�Z���V�F�[�_�[�p
			Direct3D::pContext->UpdateSubresource(pConstantBuffer_, 0, nullptr, &cb, 0, 0);
			Direct3D::pContext->DrawIndexed(indexCount_[i], 0, 0);
	}

	//ToPipeLine(transform);

	////���_�A�C���f�b�N�X�A�R���X�^���g�o�b�t�@���Z�b�g
	//bufferSet();
}

void Fbx::RayCast(RayCastData& ray,Transform& transform)
{
	for (int material = 0; material < materialCount_; material++)
	{
		XMVECTOR vDir = XMLoadFloat3(&ray.dir);
		vDir = XMVector3Normalize(vDir);
		XMStoreFloat3(&ray.dir, vDir);
		float prev = 9999.0f;

		XMVECTOR nmlVec1;
		XMVECTOR nmlVec2;
		for (int poly = 0; poly < indexCount_[material]; poly++)
		{
			XMFLOAT3 v0 = {0,0,0};
			XMStoreFloat3(&v0, pVertices_[ppIndex_[material][poly]].position);

			XMFLOAT3 v1 = { 0,0,0 };
			XMStoreFloat3(&v1, pVertices_[ppIndex_[material][poly+1]].position);

			XMFLOAT3 v2 = { 0,0,0 };
			XMStoreFloat3(&v2, pVertices_[ppIndex_[material][poly+2]].position);

			nmlVec1 = pVertices_[ppIndex_[material][poly + 1]].position - pVertices_[ppIndex_[material][poly]].position;
			nmlVec2 = pVertices_[ppIndex_[material][poly + 2]].position - pVertices_[ppIndex_[material][poly]].position;
			poly += 2;

			XMVECTOR hitPosition;
			if (Math::Intersect(ray.start,ray.dir, v0, v1, v2,ray.dist,hitPosition)&&ray.dist<prev)
			{
				ray.normal = XMVector3Normalize(XMVector3Cross(nmlVec1, nmlVec2));
				ray.dist=
				prev = ray.dist;
				ray.hitPos = XMVector3TransformCoord(hitPosition, transform.GetWorldMatrix());
				ray.hit = true;
			}

		}
	}
}


void Fbx::Release()
{
	SAFE_DELETE(indexCount_);
	SAFE_RELEASE(pConstantBuffer_);

	for (int i = 0; i < materialCount_; i++)
	{
		SAFE_RELEASE(pIndexBuffer_[i]);
	}
	SAFE_DELETE_ARRAY(pIndexBuffer_);

	SAFE_RELEASE(pVertexBuffer_);
}