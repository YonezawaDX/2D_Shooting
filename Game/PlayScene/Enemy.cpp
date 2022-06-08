#include "Enemy.h"

#include "../GameMain.h"
#include "Database.h"
#include "../GameData.h"
#include <math.h>

// 敵の情報
enum ENEMY_STATE
{
	ENEMY_STATE_ACTIVE,		// 通常状態
	ENEMY_STATE_BOMB,		// やられ状態
};

// 敵の生存範囲
#define ENEMY_ALIVE_AREA		100


// 開始座標
#define ENEMY_START				110
#define ENEMY_START_POS_X		(SCREEN_RIGHT - ENEMY_ALIVE_AREA + ENEMY_START)
#define ENEMY_START_POS_Y		(SCREEN_BOTTOM - 50)

// 通常敵の弾発射間隔
#define ENEMY_NORMAL_SHOT_INTERVAL		60

// 円周率
#define PI						3.141593f
#define COUNT_1					40.0f
#define COUNT_2					4.0f

/*---------------------------------------------------------
初期化
引数		:int textureHandle(画像ハンドル), int enemyType(種類), BulletManager* pBulletManager(弾の管理者のポインタ)
---------------------------------------------------------*/
void Enemy::Initialize(int textureHandle, int enemyType, BulletManager* pBulletManager)
{
	// 弾の種類を保存
	mType = enemyType;

	// 弾の情報を取得
	const EnemyData data = Database::msEnemyData[enemyType];

	// 画像の設定
	mSprite.SetTexture(textureHandle);
	mSprite.src.x = data.mRectX1;
	mSprite.src.y = data.mRectY1;
	mSprite.size.x = data.mRectX2;
	mSprite.size.y = data.mRectY2;

	mSprite.scale.x = 1.0f;
	mSprite.scale.y = 1.0f;

	// HPの初期化
	mHp = data.mHp;

	// 初期座標の設定(縦方向はランダム)
	mPos.y = (float)GetRand(ENEMY_START_POS_Y);
	mPos.x = ENEMY_START_POS_X;

	// 画像に座標を反映
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// 状態の初期化
	mState = ENEMY_STATE_ACTIVE;

	// 弾の管理者ポインタ（連絡先）
	mpBulletManager = pBulletManager;

	// 使用状態とする
	mIsActive = TRUE;

	// 当たり判定の初期化
	mCollision.mRadius = data.mRadius;
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;

	// タイマーの初期化
	mShotTimer = 0;
	mBombTimer = 0;

	// 敵のやられ音
	mBombSe = LoadSoundMem("Resources/Audio/swing34.wav");
}

/*-------------------------------------------------------
更新
-----------------------------------------------------*/
void Enemy::Update(void)
{

	// アクティブ状態でなければ処理しない
	if (mIsActive == FALSE)
	{
		return;
	}

	// 敵情報の取得
	const EnemyData data = Database::msEnemyData[mType];

	// 敵の種類に応じた動き
	switch (mType)
	{
		case ENEMY_TYPE_NORMAL:
		{
			// 発射間隔用タイマーを進める
			++mShotTimer %= ENEMY_NORMAL_SHOT_INTERVAL;

			// 時間が来たら弾発射
			if (mShotTimer == 0)
			{
				mpBulletManager->Shot(BULLET_TYPE_ENEMY_NORMAL, SHOOTER_TYPE_ENEMY, mPos);
			}

			break;
		}

	}
	
	// 状態に応じた処理
	switch (mState)
	{
		// 通常状態
		case ENEMY_STATE_ACTIVE:
		{
			counter++;
			mPos.x -= data.mVel;
			//sinカーブ
			mPos.y -= sinf(PI*counter/COUNT_1) * COUNT_2;
			break;
		}

		// やられ状態
		case ENEMY_STATE_BOMB:
		{
			// タイマーをすすめる
			mBombTimer++;

			// スコア
			g_gameData.mBreakScore += data.mScore;


			if (mBombTimer == 5)
			{

				PlaySoundMem(mBombSe, DX_PLAYTYPE_BACK, TRUE);
				mSprite.src.x = 48;
			}
			else if (mBombTimer == 10)
			{
				mSprite.src.x = 64;
			}
			else if (mBombTimer == 15)
			{
				mSprite.src.x = 80;
			}
			else if (mBombTimer >= 20)
			{
				// 爆破が終了したら未使用状態にする
				mIsActive = FALSE;

				// 撃破数を1機増やす
				g_gameData.mBreakNum++;
			}

			break;
		}
	}

	// 生存範囲外に出たら未使用状態にする
	if (
		mPos.x < SCREEN_LEFT - ENEMY_ALIVE_AREA ||
		mPos.x > SCREEN_RIGHT + ENEMY_ALIVE_AREA ||
		mPos.y < SCREEN_TOP - ENEMY_ALIVE_AREA ||
		mPos.y > SCREEN_BOTTOM + ENEMY_ALIVE_AREA
		)
	{
		mIsActive = FALSE;
	}

	// 画像に座標を反映
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// 当たり判定に座標を更新
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;
}

/*--------------------------------------------------
描画
---------------------------------------------------*/
void Enemy::Draw(void)
{
	// アクティブ状態でなければ処理しない
	if (mIsActive == FALSE)
	{
		return;
	}

	mSprite.Draw();
}

/*-------------------------------------------------
ダメージ処理
--------------------------------------------------*/
void Enemy::Damage(int damage)
{
	// 体力を削る
	mHp -= damage;

	// 体力がなくなっていたら爆破状態へ
	if (mHp <= 0)
	{
		mState = ENEMY_STATE_BOMB;

		// 見た目を爆破状態へ
		mSprite.src.x = 32;
		mSprite.src.y = 80;
		mSprite.size.x = 16;
		mSprite.size.y = 16;

		mSprite.scale.x = 3.0f;
		mSprite.scale.y = 3.0f;
	}
}
