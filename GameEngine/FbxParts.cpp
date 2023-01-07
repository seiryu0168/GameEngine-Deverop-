#include "FbxParts.h"

#include"Engine/Direct3D.h"

FbxParts::FbxParts()
{
	pVertexBuffer_ = nullptr;
	ppIndexBuffer_ = nullptr;
	pConstantBuffer_ = nullptr;


}

FbxParts::~FbxParts()
{
	SAFE_DELETE(pVertices_);
	SAFE_RELEASE(pVertexBuffer_);

	SAFE_DELETE_ARRAY(ppIndexBuffer_);
	SAFE_RELEASE(pConstantBuffer_);

	//SAFE_DELETE(pSkinInfo_);
	SAFE_DELETE(ppCluster_);
	if (pWeightArray_ != nullptr)
	{
		for (int i = 0; i < vertexCount_; i++)
		{
			SAFE_DELETE_ARRAY(pWeightArray_);
			SAFE_DELETE_ARRAY(pBoneArray_);

		}
	}

	for (int i = 0; i < materialCount_; i++)
	{
		SAFE_RELEASE(ppIndexBuffer_[i]);
		SAFE_DELETE(pMaterialList_[i].pTexture);
		SAFE_DELETE_ARRAY(ppIndex_);

	}
	int* indexCount_;

}

HRESULT FbxParts::Init(FbxNode* pNode)
{
	FbxMesh* mesh = pNode->GetMesh();

	//�e���̌����擾
	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
	polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount();//�}�e���A���̐�

	InitVertex(mesh);
	InitIndex(mesh);
	CreateConstantBuffer();
	InitMaterial(pNode);
	return E_NOTIMPL;
}

HRESULT FbxParts::InitVertex(fbxsdk::FbxMesh* mesh)
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
#if 1
		if (mesh->GetElementTangentCount() > 0)
		{
			for (int vertex = 0; vertex < 3; vertex++)
			{
				int index = mesh->GetPolygonVertex(poly, vertex);
				//�ڐ�
				FbxGeometryElementTangent* t = mesh->GetElementTangent(0);
				FbxVector4 tangent = t->GetDirectArray().GetAt(index).mData;
				pVertices_[index].tangent = XMVectorSet((float)tangent[0], (float)tangent[1], (float)tangent[2], 0.0f);
			}
		}
		else
		{
			for (int vertex = 0; vertex < 3; vertex++)
			{
				int index = mesh->GetPolygonVertex(poly, vertex);
				pVertices_[index].tangent = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
#endif
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
HRESULT FbxParts::InitIndex(fbxsdk::FbxMesh* mesh)
{
	ppIndex_ = new int* [materialCount_];
	ppIndexBuffer_ = new ID3D11Buffer * [materialCount_];
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
		HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &ppIndexBuffer_[i]);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s", L"�G���[", MB_OK);
			return hr;
		}
	}
	return S_OK;
}

//////////////////////////////////�R���X�^���g�o�b�t�@�쐬///////////////////////////////////	
HRESULT FbxParts::CreateConstantBuffer()
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

HRESULT FbxParts::InitSkelton(FbxMesh* pMesh)
{
	FbxDeformer* pDeformer = pMesh->GetDeformer(0);
	if (pDeformer == nullptr)
	{
		return;
	}
	pSkinInfo_ = (FbxSkin*)pDeformer;

	struct POLY_INDEX
	{
		int* polyIndex;
		int* vertexIndex;
		int refNum;
	};

	POLY_INDEX* polyTable = new POLY_INDEX[vertexCount_];
	for (int i = 0; i < vertexCount_; i++)
	{
		polyTable[i].polyIndex = new int[polygonCount_ * 3];
		polyTable[i].vertexIndex = new int[polygonCount_ * 3];
		polyTable[i].refNum = 0;
		ZeroMemory(polyTable[i].polyIndex, sizeof(int)* polygonCount_ * 3);
		ZeroMemory(polyTable[i].vertexIndex, sizeof(int)* polygonCount_ * 3);

		for (int j = 0; j < polygonCount_; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (pMesh->GetPolygonVertex(j, k) == i)
				{
					polyTable[i].polyIndex[polyTable[i].refNum] = j;
					polyTable[i].vertexIndex[polyTable[i].refNum] = k;
					polyTable[i].refNum++;
				}
			}
		}
	}

	//�{�[�����擾
	boneNum_ = pSkinInfo_->GetClusterCount();
	ppCluster_ = new FbxCluster * [boneNum_];
	for (int i = 0; i < boneNum_; i++)
	{
		ppCluster_[i] = pSkinInfo_->GetCluster(i);
	}

	//�{�[���̐��ɍ��킹�ăE�F�C�g��������
	pWeightArray_ = new FbxParts::WEIGHT[vertexCount_];
	for (int i = 0; i < vertexCount_; i++)
	{
		pWeightArray_[i].originPos = pVertices_[i].position;
		pWeightArray_[i].originNormal = pVertices_[i].normal;
		pWeightArray_[i].pBoneIndex = new int[boneNum_];
		pWeightArray_[i].pBoneWeight = new float[boneNum_];
		for (int j = 0; j < boneNum_; j++)
		{
			pWeightArray_[i].pBoneIndex[j] = -1;
			pWeightArray_[i].pBoneWeight[j] = 0.0f;
		}
	}

	//�e�{�[������e�����󂯂钸�_�𒲂ׁA���_�x�[�X��boneIndex�AWeight�𐮓ڂ���
	for (int i = 0; i < boneNum_; i++)
	{
		int indexNum = ppCluster_[i]->GetControlPointIndicesCount();
		int* piIndex = ppCluster_[i]->GetControlPointIndices();
		double* pdWeight = ppCluster_[i]->GetControlPointWeights();
		
		//���_�Ɋ֘A�t����ꂽ�E�F�C�g���5�ȏ�̏ꍇ�͏d�݂̑傫������4�{�ɍi��
		for (int j = 0; j < indexNum; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (k >= boneNum_)
					break;
				if (pdWeight[j] > pWeightArray_[piIndex[j]].pBoneWeight[k])
				{
					for (int l = boneNum_ - 1; l > k; l--)
					{
						pWeightArray_[piIndex[j]].pBoneIndex[l] = pWeightArray_[piIndex[j]].pBoneIndex[l - 1];
						pWeightArray_[piIndex[j]].pBoneWeight[l] = pWeightArray_[piIndex[j]].pBoneWeight[l - 1];
					}
					pWeightArray_[piIndex[j]].pBoneIndex[k] = i;
					pWeightArray_[piIndex[j]].pBoneWeight[k] = (float)pdWeight[j];
				}
			}
		}
	}
	
	//�{�[���̐���
	pBoneArray_ = new FbxParts::BONE[boneNum_];
	for (int i = 0; i < boneNum_; i++)
	{
		//�{�[���̃f�t�H���g�ʒu���擾
		FbxAMatrix matrix;
		ppCluster_[i]->GetTransformLinkMatrix(matrix);

		//�s����R�s�[
		XMFLOAT4X4 pose;
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				pose(x, y) = (float)matrix.Get(x, y);
			}
		}
	}

	//�ꎞ�I�Ɏ���Ă������������J��
	for (int i = 0; i < vertexCount_; i++)
	{
		SAFE_DELETE_ARRAY(polyTable[i].polyIndex);
		SAFE_DELETE_ARRAY(polyTable[i].vertexIndex);
	}
	SAFE_DELETE_ARRAY(polyTable);
	return E_NOTIMPL;
}

void FbxParts::InitMaterial(fbxsdk::FbxNode* pNode)
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
		int count = lProperty.GetSrcObjectCount<FbxFileTexture>();
		if (lProperty.GetSrcObjectCount<FbxFileTexture>() > 0)
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

		/////////////////////////////////�m�[�}���}�b�v//////////////////////////
		{
			FbxProperty IPropaty = pMaterial->FindProperty(FbxSurfaceMaterial::sBump);
			int normalMapCount = IPropaty.GetSrcObjectCount<FbxFileTexture>();

			if (normalMapCount != 0)
			{
				FbxFileTexture* textureInfo = IPropaty.GetSrcObject<FbxFileTexture>(0);
				const char* textureFilePath = textureInfo->GetRelativeFileName();

				//�t�@�C����+�g�������ɂ���
				char name[_MAX_FNAME];	//�t�@�C����
				char ext[_MAX_EXT];	//�g���q
				_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);

				sprintf_s(name, "%s%s", name, ext);

				//�t�@�C������e�N�X�`���쐬
				wchar_t wtext[FILENAME_MAX];
				size_t ret;
				mbstowcs_s(&ret, wtext, name, strlen(name));

				pMaterialList_[i].pNormalMap = new Texture;
				pMaterialList_[i].pNormalMap->Load(wtext);
			}
			else
			{
				pMaterialList_[i].pNormalMap = nullptr;
			}
		}
	}
}