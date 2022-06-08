#include "BulletManager.h"

#include "Enemy.h"
#include "Player.h"


/*-----------------------------------------------
初期化
引数	: int textureHandle(弾の画像ハンドル)
---------------------------------------------------*/
void BulletManager::Initialize(int textureHandle)
{
	mTextureHandle = textureHandle;

	
	// すべての弾を未使用状態にする
	for (int i = 0; i < BULLET_NUM; i++)
	{
		mBullets[i].mIsActive = FALSE;
	}
}

/*------------------------------------------------
更新
---------------------------------------------------*/
void BulletManager::Update(void)
{
	// プレイヤーの弾の更新
	for (int i = 0; i < BULLET_NUM; i++)
	{
		mBullets[i].Update();
	}
}

/*------------------------------------------------
描画
------------------------------------------------------*/
void BulletManager::Draw(void)
{
	// プレイヤーの弾の更新
	for (int i = 0; i < BULLET_NUM; i++)
	{
		mBullets[i].Draw();
	}
}

/*--------------------------------------------------
弾の発射
------------------------------------------------------*/
BOOL BulletManager::Shot(int bulletType, int shooterType, Float2 pos)
{
	BOOL res = FALSE;

	// 発射可能な弾を探す
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// アクティブ(使用中)なら次へ
		if (mBullets[i].mIsActive == TRUE)
		{
			continue;
		}

		// 使用されていないなら初期化
		mBullets[i].Initialize(mTextureHandle, bulletType, shooterType, pos);

		// 弾の発射に成功
		res = TRUE;

		// 処理を中断する
		break;
	}

	return res;
}

/*--------------------------------------------
弾と渡された対象との当たり判定
----------------------------------------------*/
void BulletManager::CheckHitEnemy(Enemy* pEnemy)
{
	// すべての弾と渡された対象の判定を取る
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// 特定の条件下ならば処理しない
		if (
			mBullets[i].mIsActive == FALSE ||				// 弾が使用状態でない								// 敵の体力がない
			pEnemy->mHp <= 0 ||								// 敵の体力がない
			mBullets[i].mShooterType == SHOOTER_TYPE_ENEMY	// 敵の発射した弾だった
			)
		{
			continue;
		}

		// 当たっていなければ次へ
		if (mBullets[i].mCollision.CheckHit(pEnemy->mCollision) == FALSE)
		{
			continue;
		}

		// 体力を減らす
		pEnemy->Damage(mBullets[i].mPower);

		// 弾を未使用状態にする
		mBullets[i].mIsActive = FALSE;
	}
}

/*---------------------------------------------
弾とプレイヤーの当たり判定
----------------------------------------------*/
void BulletManager::CheckHitPlayer(Player* pPlayer)
{
	// すべての弾と渡された対象を取る
	for (int i = 0; i < BULLET_NUM; i++)
	{
		// 特定の条件ならば処理しない
		if (
			mBullets[i].mIsActive == FALSE ||					// 弾が使用状態でない
			mBullets[i].mShooterType == SHOOTER_TYPE_PLAYER ||	// プレイヤーの発射した弾だった
			pPlayer->IsDamage() == TRUE							// プレイヤーが被弾中
			)
		{
			continue;
		}

		// 当たっていなければ次へ
		if (mBullets[i].mCollision.CheckHit(pPlayer->mCollision) == FALSE)
		{
			continue;
		}

		// ダメージ処理
		pPlayer->Damage();

		// 弾を未使用状態にする
		mBullets[i].mIsActive = FALSE;
	}
}
