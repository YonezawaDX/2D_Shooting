#include "PlayScene.h"

#include "../GameMain.h"
#include "../GameData.h"

// シーンの状態
enum PLAY_STATE
{
	PLAY_STATE_INITIALIZE,		// 初期化

	PLAY_STATE_FADEIN,			// フェードイン待ちの状態
	PLAY_STATE_MAIN,			// メイン処理
	PLAY_STATE_FADEOUT,			// フェードアウト状態

	PLAY_STATE_FINALIZE,		// 終了処理

};

/*------------------------------------------------------------------
初期化
--------------------------------------------------------------------*/
void PlayScene::Initialize(void)
{
	mShootingHandle = LoadGraph("Resources/Textures/allgame1.png");

	// 変数などのリセット
	Reset();
}

/*----------------------------------------------------------
情報のリセット
------------------------------------------------------------*/
void PlayScene::Reset(void)
{
	// 状態の初期化
	mState = PLAY_STATE_INITIALIZE;

	// プレイヤーの初期化
	mPlayer.Initialize(mShootingHandle, &mBulletManage);

	// 弾の管理者の初期化
	mBulletManage.Initialize(mShootingHandle);

	// 敵の管理者の初期化
	mEnemyManager.Initialize(mShootingHandle, &mBulletManage);

	// 背景の初期化
	mBackGround.Initialize();

	mUserInterface.Initialize();

}

/*-----------------------------------------------------------
更新
-------------------------------------------------------------*/
int PlayScene::Update(void)
{
	int nextScene = GAME_SCENE_NONE;

	switch (mState)
	{
		// 初期化      =================================
		case PLAY_STATE_INITIALIZE:
		{
			
			// 変数などのリセット
			Reset();

			// ゲームデータの初期化
			g_gameData.Initialize();

			// フェードイン状態へ
			mState = PLAY_STATE_FADEIN;

			break;
		}
			// フェードイン　　　========================
		case PLAY_STATE_FADEIN:
		{
			// フェードの更新
			int res = FadeInUpdate(FADE_TIME);

			// フェードが終了したら次の状態へ
			if (res == FALSE)
			{
				mState = PLAY_STATE_MAIN;
			}

			break;
		}
		// メイン処理	    ========================
		case PLAY_STATE_MAIN:
		{
			// プレイヤーの更新
			mPlayer.Update();

			// 弾の管理者の更新
			mBulletManage.Update();

			// 敵の管理者の更新
			mEnemyManager.Update();

			// 敵と弾との当たり判定
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				// 未使用状態なら処理しない
				if (mEnemyManager.mEnemies[i].mIsActive == FALSE)
				{
					continue;
				}

				mBulletManage.CheckHitEnemy(&mEnemyManager.mEnemies[i]);
			}
			// プレイヤーと弾の当たり判定
			mBulletManage.CheckHitPlayer(&mPlayer);

			// 敵とプレイヤーとの当たり判定
			mEnemyManager.CheckHitPlayer(&mPlayer);

			// 敵がいなくなったらゲーム終了
			if (mEnemyManager.IsEnd() == TRUE)
			{
				mState = PLAY_STATE_FADEOUT;
			}

			// 2回敵に当たって終了
			if (g_gameData.mStock == 0)
			{
				mState = PLAY_STATE_FADEOUT;
			}

			break;
		}
		// フェードアウト　　====================
		case PLAY_STATE_FADEOUT:
		{
			// フェードの更新
			int res = FadeOutUpdate(FADE_TIME);

			// フェードが終了したら次の状態へ
			if (res == FALSE)
			{
				mState = PLAY_STATE_FINALIZE;
			}

			break;
		}
		// 終了処理　　=========================
		case PLAY_STATE_FINALIZE:
		{
			// 次のシーンへ
			nextScene = GAME_SCENE_RESULT;

			// 変数などのリセット
			Reset();

			break;
		}
	}

	return nextScene;
}

/*-------------------------------------------------
描画
-------------------------------------------------*/
void PlayScene::Draw(void)
{
	// 背景の描画
	mBackGround.Draw();
	
	// プレイヤーの描画
	mPlayer.Draw();

	// 弾の管理者の描画
	mBulletManage.Draw();

	// 敵の管理者の描画
	mEnemyManager.Draw();

	//ユーザーインターフェースの描画
	mUserInterface.Draw();
}

/*---------------------------------------------------
終了処理
------------------------------------------------------*/
void PlayScene::Finalize(void)
{
	DeleteGraph(mShootingHandle);

}



