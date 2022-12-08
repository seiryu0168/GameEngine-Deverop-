#include "EnemyNormal.h"
#include"Engine/Model.h"
#include"Engine/BoxCollider.h"
#include"Pointer.h"
//コンストラクタ
EnemyNormal::EnemyNormal(GameObject* parent)
	:Enemy(parent, "EnemyNormal"),
	hModel_(-1)
{

}

//デストラクタ
EnemyNormal::~EnemyNormal()
{
	Release();
}

//初期化
void EnemyNormal::Initialize()
{
	hModel_ = Model::Load("Assets\\Enemy2.fbx");
	SetPlayerPointer((Player*)FindObject("Player"));
	OBBCollider* pCollider = new OBBCollider(XMFLOAT3(1,1,1),false,false);
	AddCollider(pCollider);
	Model::SetModelNum(hModel_);

	transform_.position_.x = std::rand() % 100;
	transform_.position_.y = std::rand() % 100;
	transform_.position_.z = std::rand() % 100;
}

//更新
void EnemyNormal::Update()
{
	GetPositionVec() =XMLoadFloat3(&transform_.position_);    //今の座標をvPositionに入れる
	
	////////////////エネミーの処理/////////////
	XMFLOAT3 aa = GetPlayerPointer()->GetPosition();		//プレイヤーの座標取得
	SetToPlayerVec(XMLoadFloat3(&aa) - GetPositionVec());	//エネミーからプレイヤーに向かうベクトルを作成

	if (IsVisible(GetFrontVec(),0.5,50.0f))
	{
		EnemyMove();

	}
}

void EnemyNormal::FixedUpdate()
{

}

//描画
void EnemyNormal::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void EnemyNormal::EnemyMove()
{
	SetPositionVec(XMLoadFloat3(&transform_.position_));//vPositionに今の座標を入れる
	XMFLOAT3 playerPos = GetPlayerPointer()->GetPosition();
	XMVECTOR toTargetVec = XMLoadFloat3(&playerPos);
	XMVECTOR toVec = toTargetVec - GetPositionVec();
	toVec = XMVector3Normalize(toVec);							//引数の正規化
	float angle = XMVectorGetX(XMVector3Dot(GetFrontVec(), toVec)); //角度計算(ラジアン)
	transform_.rotate_.y = 1-angle;
	SetMatrixY(XMMatrixRotationY(transform_.rotate_.y));			//角度を回転行列に変換
	SetFrontVec(XMVector3TransformCoord(toVec, GetMatrixY()));			//前方向ベクトルを回転
	toVec *= 0.6f;
	toVec += GetPositionVec();
	SetPositionVec(toVec);
	XMStoreFloat3(&transform_.position_, toVec);
}

void EnemyNormal::Attack()
{

}

void EnemyNormal::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		if (GetPlayerPointer()->GetSatatus() & ATC_ATTACK)
		{
			DecreaseLife(1);
			GetPlayerPointer()->SetStatus(ATC_DEFAULT);
			if (GetLife() < 0)
			{
				Transform pos;
				pos.position_= { 9999,9999,9999 };
				Model::SetTransform(hModel_,pos);
				KillMe();
			}
		}
	}
}

//開放
void EnemyNormal::Release()
{
}