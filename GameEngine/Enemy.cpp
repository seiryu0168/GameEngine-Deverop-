#include "Enemy.h"
#include"StateList.h"
//コンストラクタ
Enemy::Enemy(GameObject* parent, std::string name)
	:GameObject(parent, name)
{
	
	enemyParameter_.life = 3;
	enemyParameter_.viewRange = 50.0f;
	enemyParameter_.viewAngle = 0.5f;
	enemyParameter_.toPlayerVec = XMVectorSet(0, 0, 0, 0);
	enemyParameter_.frontVec = XMVectorSet(0, 0, 1, 0);
	enemyParameter_.upVec = XMVectorSet(0, 1, 0, 0);
	enemyParameter_.matX = XMMatrixIdentity();
	enemyParameter_.matY; XMMatrixIdentity();
	enemyParameter_.visibleFlag = false;
	enemyParameter_.isTargetList = false;
	enemyParameter_.vPosition = XMLoadFloat3(&transform_.position_);
	enemyParameter_.pPlayer = nullptr;
	ChangeState(State::search->GetInstance());
}

//デストラクタ
Enemy::~Enemy()
{

}

bool Enemy::IsVisible( float visibleAngle, float range)
{

	XMVECTOR toPlayer;
	XMFLOAT3 playerPos = GetPlayerPointer()->GetPosition();
	enemyParameter_.toPlayerVec = XMLoadFloat3(&playerPos) - enemyParameter_.vPosition;
	float toPlayerRange;
	toPlayerRange = XMVectorGetX(XMVector3Length(enemyParameter_.toPlayerVec));			//視界判定用の視界の長さ取得
	toPlayer = XMVector3Normalize(enemyParameter_.toPlayerVec);							//正規化

	XMVECTOR dot = XMVector3Dot(GetFrontVec(), toPlayer);								//内積を計算
	float angle = acos(min(XMVectorGetX(dot), 1));										//角度計算(1以上にならないようmin関数つけた)
	if (toPlayerRange <= 2 * range)
	{
		enemyParameter_.pPlayer->AddTargetList(this);
		enemyParameter_.isTargetList = true;
		if (angle<visibleAngle && angle>-visibleAngle && toPlayerRange < range)
		{
			enemyParameter_.frontVec = toPlayer;
			return true;
		}
	}
	else
	{
		enemyParameter_.isTargetList = false;
	}

	return false;
}
void Enemy::ChangeState(EnemyState* state)
{
	pEnemyState_ = state;
	pEnemyState_->Init(this);
}