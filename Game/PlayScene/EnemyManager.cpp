/*
敵の管理
作成日 : 2020/06/30
作成者 : 米澤駿介
*/
#include "EnemyManager.h"

#include "Database.h"
#include "Player.h"

/*----------------------------------------------------
初期化
引数 : int textureHandle(敵の画像ハンドル)
-------------------------------------------------------*/
void EnemyManager::Initialize(int textureHandle, BulletManager* pBulletManager)
{
	mTextureHandle = textureHandle;

	// タイマーの初期化
	mTimer = 0;

	// 弾の管理者のポインタ（連絡先）
	mpBulletManager = pBulletManager;

	// 要素番号の初期化
	mArrivalIdx = 0;

	// すべての敵を未使用状態にする
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		mEnemies[i].mIsActive = FALSE;
	}
}

/*----------------------------------------------------
更新
------------------------------------------------------*/
void EnemyManager::Update()
{
	// タイマーを進める
	mTimer++;

	// 敵の出現条件を満たしていたら生成
	EnemyArrivalData arrival = Database::mEnemyArrivalData[mArrivalIdx];

	while (arrival.mArrivalTime == mTimer && mArrivalIdx < ENEMY_ARRIVAL_NUM)
	{
		// 敵の生成処理
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			// すでに動いている敵は無視
			if (mEnemies[i].mIsActive == TRUE)
			{
				continue;
			}

			// 敵の生成
			mEnemies[i].Initialize(mTextureHandle, arrival.mEnemyType, mpBulletManager);

			// 次の生成状態を見る
			mArrivalIdx++;

			// 次の要素を取得
			arrival = Database::mEnemyArrivalData[mArrivalIdx];

			break;
		}
	}

	// 敵の更新
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		mEnemies[i].Update();
	}
}

/*-----------------------------------------------
描画
------------------------------------------------*/
void EnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		mEnemies[i].Draw();
	}
}

/*-------------------------------------------------
敵とプレイヤーの当たり判定
--------------------------------------------------*/
void EnemyManager::CheckHitPlayer(Player* pPlayer)
{
	// すべての弾と渡された対象の判定をとる
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// 特定の条件ならば処理しない
		if (
			mEnemies[i].mIsActive == FALSE ||			// 弾が使用状態でない
			pPlayer->IsDamage() == TRUE					// プレイヤーが被弾中
			)
		{
			continue;
		}

		// 当たっていなければ次へ
		if (mEnemies[i].mCollision.CheckHit(pPlayer->mCollision) == FALSE)
		{
			continue;
		}

		// ダメージ処理
		pPlayer->Damage();

		break;
	}
}

/*------------------------------------------------------
終了処理
----------------------------------------------------*/
BOOL EnemyManager::IsEnd(void)
{
	EnemyArrivalData arrival = Database::mEnemyArrivalData[mArrivalIdx];

	if (arrival.mArrivalTime != 0)
	{
		return FALSE;
	}

	// 敵が出現していないか確認
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (mEnemies[i].mIsActive ==TRUE)
		{
			return FALSE;
		}
	}

	return TRUE;
}