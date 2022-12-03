#include "Model.h"
#include<vector>
//#include"Direct3D.h"
namespace Model
{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string fileName_;
	};
	std::vector<ModelData*> modelData_;
	std::vector<int> polygonTestList_;
};

int Model::Load(std::string fileName)
{
	ModelData* pModelData = new ModelData;
	pModelData->fileName_ = fileName;
	pModelData->pfbx_ = nullptr;

	//既にあるファイルと名前が同じならそのアドレスを代入する
	for (auto itr = modelData_.begin(); itr != modelData_.end(); itr++)
	{
		if (fileName == (*itr)->fileName_)
		{
			pModelData->pfbx_ = (*itr)->pfbx_;
			break;
		}
	}

	if (pModelData->pfbx_==nullptr)
	{
		pModelData->pfbx_ = new Fbx;
		pModelData->pfbx_->Load(fileName);
	}
	modelData_.push_back(pModelData);
	return modelData_.size() - 1;
}

void Model::SetTransform(int modelNum, Transform transform)
{
	if (modelData_[modelNum] != nullptr)
	{
		modelData_[modelNum]->transform_ = transform;
	}
}
void Model::Draw(int modelNum)
{
	if (modelData_[modelNum]->pfbx_ != nullptr)
	{
		modelData_[modelNum]->pfbx_->Draw(modelData_[modelNum]->transform_, SHADER_3D);
	}
}

void Model::RayCast(int modelNum, RayCastData& ray)
{
	XMMATRIX invW = XMMatrixInverse(nullptr,modelData_[modelNum]->transform_.GetWorldMatrix());
	XMVECTOR vStart = XMLoadFloat3(&ray.start);
	XMVECTOR vPass = XMVectorSet(ray.start.x+ray.dir.x, ray.start.y + ray.dir.y, ray.start.z + ray.dir.z,0);

	vStart = XMVector3TransformCoord(vStart, invW);
	vPass= XMVector3TransformCoord(vPass, invW);

	XMStoreFloat3(&ray.start, vStart);
	XMStoreFloat3(&ray.dir, vPass - vStart);
	modelData_[modelNum]->pfbx_->RayCast(ray,modelData_[modelNum]->transform_);
}

void Model::RayCast(RayCastData& ray)
{
	bool isHit = false;
	float length = 9999;
	XMVECTOR hitPos = XMVectorSet( 0,0,0,0 );
	XMVECTOR normal= XMVectorSet(0, 0, 0, 0);
	for (int i = 0; i < polygonTestList_.size(); i++)
	{

		XMMATRIX invW = XMMatrixInverse(nullptr, modelData_[polygonTestList_[i]]->transform_.GetWorldMatrix());
		XMVECTOR vStart = XMLoadFloat3(&ray.start);
		XMVECTOR vPass = XMVectorSet(ray.start.x + ray.dir.x, ray.start.y + ray.dir.y, ray.start.z + ray.dir.z, 0);

		vStart = XMVector3TransformCoord(vStart, invW);
		vPass = XMVector3TransformCoord(vPass, invW);

		XMStoreFloat3(&ray.start, vStart);
		XMStoreFloat3(&ray.dir, vPass - vStart);
		modelData_[polygonTestList_[i]]->pfbx_->RayCast(ray, modelData_[polygonTestList_[i]]->transform_);
		if (ray.hit&&length>ray.dist)
		{
			isHit = ray.hit;
			length = ray.dist;
			hitPos = ray.hitPos;
			normal = ray.normal;
		}
	}
	ray.dist = length;
	ray.hit = isHit;
	ray.hitPos = hitPos;
	ray.normal = normal;
}

void Model::SetModelNum(int modelNum)
{
	polygonTestList_.push_back(modelNum);
}

void Model::DeleteModelNum(int modelNum)
{
		auto itr = polygonTestList_.begin();
	for (int i = 0; i <  polygonTestList_.size(); i++)
	{
		if (polygonTestList_[i] == modelNum)
		{
			polygonTestList_.erase(itr);
			return;
			
		}
		itr++;
	}
}

//複数のポインタが同じアドレスを参照してるから参照してない所までmodelData_を進めなきゃいけない
void Model::Release()
{
	for (int i = 0; i < modelData_.size(); i++)
	{
		bool isRef = false;//参照しているかどうかのフラグ
		for (int j = i + 1; j < modelData_.size(); j++)
		{
			//同じものが参照されてたらtrue
			if (modelData_[i]->pfbx_ == modelData_[j]->pfbx_)
			{
				isRef = true;
			}
		}
		//もう参照されてないなら解放
		if (!isRef)
		{
			SAFE_DELETE(modelData_[i]->pfbx_);
		}

		SAFE_DELETE(modelData_[i]);
	}
	modelData_.clear();
}