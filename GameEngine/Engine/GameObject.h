#pragma once
#include<string>
#include<list>
#include"BoxCollider.h"
#include"SphereCollider.h"
#include"Transform.h"

class GameObject
{
	friend class Collider;
protected:
	std::list<GameObject*> childList_;	//�q���X�g
	std::list<Collider*> colliderList_; //�R���C�_�[���X�g
	Transform	transform_;				//�I�u�W�F�N�g�̏��
	GameObject* pParent_;				//�e�I�u�W�F�N�g�̏��
	std::string	objectName_;			//���O
	bool killFlag;						//�L�����邩�ǂ���

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void Draw()       = 0;
	virtual void Release()    = 0;

	void UpdateSub();
	void FixedUpdateSub();
	void DrawSub();
	void ReleaseSub();

	template<class T>
	T* Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		if (parent != nullptr)
		{
			parent->PushBackChild(p);
		}
		p->Initialize();
		return p;
	}

	void KillMe()
	{
		killFlag = true;
	}

	///////////////////////////�Փˊ֘A�̊֐�////////////////////////
	virtual void OnCollision(GameObject* pTarget) {};
			void Collision(GameObject* pTarget);
			void AddCollider(Collider* collider);
			void KillAllChildren();
			void KillObjectSub(GameObject* pTarget);
			void PushBackChild(GameObject* pTarget);
			
			
			Transform GetTransform();
			XMFLOAT3  GetPosition();
			XMFLOAT3  GetRotate();
			XMFLOAT3  GetScale();
			std::string GetObjectName() { return objectName_; }

	//�e�I�u�W�F�N�g�擾
	GameObject* GetParent();
	GameObject* GetRootJob();
	GameObject* FindObject(std::string name);
	GameObject* FindChild(std::string name);
	XMMATRIX    GetWorldMatrix();

	float Easing(int frameCount);
	float Easing(float time);



	//���[���h���W�擾
	XMFLOAT3    GetWorldPosition() { return Transform::Float3Add(GetParent()->transform_.position_, transform_.position_); }

};