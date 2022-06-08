/*
プレイヤー
作成日 : 2020/06/23
作成者 : 米澤駿介
*/
#include <math.h>

#include "Player.h"

#include "../GameMain.h"


// プレイヤーの状態
enum PLAYER_STATE
{
	PLAYER_STATE_ACTIVE,		// 操作できる状態
	PLAYER_STATE_BOMB,			// やられ状態
};

// 飛行機の画像の切り取り情報
#define PLAYER_RECT_X1			0
#define PLAYER_RECT_Y1			0
#define PLAYER_RECT_X2			32
#define PLAYER_RECT_Y2			32

// 飛行機ミニ画像
#define PLAYER_MINI_X1			192
#define PLAYER_MINI_Y1			0
#define PLAYER_MINI_X2			60
#define PLAYER_MINI_Y2			32

// 移動スピード
#define PLAYER_VEL				5.0f

// 弾の発射間隔
#define PLAYER_BULLET_INTERVAL		5

// 初期の残機
#define PLAYER_STOCK_DEFAULT		2

// プレイヤーの当たり判定
#define PLAYER_RADIUS				8.0f

/*----------------------------------------------------
初期化
----------------------------------------------------*/
void Player::Initialize(int textureHandle, BulletManager* pBulletManager)
{
	// 状態の初期化
	mState = PLAYER_STATE_ACTIVE;

	// 画像の設定
	mSprite.SetTexture(textureHandle);
	mSprite.src.x = PLAYER_RECT_X1;
	mSprite.src.y = PLAYER_RECT_Y1;
	mSprite.size.x = PLAYER_RECT_X2;
	mSprite.size.y = PLAYER_RECT_Y2;

	mSprite.scale.x = 1.0f;
	mSprite.scale.y = 1.0f;

	mSprite.alpha = 1.0f;

	// 初期座標の設定
	mPos.x = SCREEN_CENTER_X;
	mPos.y = SCREEN_CENTER_Y;

	// 画像に座標を反映
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// 弾の管理者のポインタ (連絡先) を保存
	mpBulletManager = pBulletManager;

	// 弾の発射間隔管理用タイマーの初期化
	mShootIntervalTimer = 0;

	// 当たり判定の初期化
	mCollision.mRadius = PLAYER_RADIUS;
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;

	// 弾の音
	mBulletSe = LoadSoundMem("Resources/Audio/pi77.wav");
}

/*----------------------------------------------------
更新
-----------------------------------------------------*/
void Player::Update(void)
{
	switch (mState)
	{
		// 操作できる状態		=========================
		case PLAYER_STATE_ACTIVE:
		{
			// タイマー処理
			++mShootIntervalTimer %= PLAYER_BULLET_INTERVAL;

			// 移動処理
			Move();

			// 弾の発射処理
			if (mShootIntervalTimer == 0 && IsButtonDown(PAD_INPUT_1) == TRUE)
			{
				mpBulletManager->Shot(BULLET_TYPE_PLAYER_POWER, SHOOTER_TYPE_PLAYER, mPos);

				// 弾の音
				PlaySoundMem(mBulletSe, DX_PLAYTYPE_BACK, TRUE);

			}

			break;
		}
		// やられ状態        =======================================
		case PLAYER_STATE_BOMB:
		{
			// タイマーを進める
			mBombTimer++;

			if (mBombTimer == 5)
			{
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
			else if(mBombTimer == 20)
			{
				mSprite.alpha = 0.0f;
			}
			else if (mBombTimer >= 60)
			{
				// 爆破が終了したら復帰させる
				mSprite.src.x = PLAYER_MINI_X1;
				mSprite.src.y = PLAYER_MINI_Y1;
				mSprite.size.x = PLAYER_MINI_X2;
				mSprite.size.y = PLAYER_MINI_Y2;


				mSprite.scale.x = 0.8f;
				mSprite.scale.y = 0.8f;

				mSprite.alpha = 1.0f;

				// 爆発タイマーの初期化
				mBombTimer = 0;

				// 操作可能状態へ
				mState = PLAYER_STATE_ACTIVE;
			}

			break;
		}
	}

	// 画像に座標を反映
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// 当たり判定に座標を反映
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;
}

/*-------------------------------------------------
描画
-------------------------------------------------*/
void Player::Draw(void)
{
	//自機の表示
	mSprite.Draw();
}

/*-----------------------------------------------------------------
プレイヤーの移動処理
-------------------------------------------------------*/
void Player::Move(void)
{
	// 移動
	int inputUD = 0;
	int inputLR = 0;

	// 上下
	if (IsButtonDown(PAD_INPUT_UP) == TRUE)
	{
		inputUD = -1;
	}

	if (IsButtonDown(PAD_INPUT_DOWN) == TRUE)
	{
		inputUD = 1;
	}

	// 左右
	if (IsButtonDown(PAD_INPUT_LEFT) == TRUE)
	{
		inputLR = -1;
	}

	if (IsButtonDown(PAD_INPUT_RIGHT) == TRUE)
	{
		inputLR = 1;
	}

	// 入力がされていないならこれ以上処理しない
	if (inputUD == 0 && inputLR == 0)
	{
		// 早期リターン
		return;
	}

	// 入力情報をベクトル計算用にflort型へ変換
	float vx = (float)inputLR;
	float vy = (float)inputUD;

	// ベクトルの長さを取得
	float vl = sqrtf((vx * vx) + (vy * vy));

	// 単位ベクトル（長さが1のベクトル）を計算
	vx /= vl;
	vy /= vl;

	// 移動ベクトルを目的の大きさ（移動量）にスケーリング
	vx *= PLAYER_VEL;
	vy *= PLAYER_VEL;

	// 移動量を座標に加算
	mPos.x += vx;
	mPos.y += vy;

	// 座標の移動制限
	mPos.x = ClampF(mPos.x, SCREEN_LEFT, SCREEN_RIGHT);
	mPos.y = ClampF(mPos.y, SCREEN_TOP, SCREEN_BOTTOM);
}

/*----------------------------------------------------
ダメージ処理
------------------------------------------------------*/
void Player::Damage(void)
{
	// 残機を1減らす
	g_gameData.mStock--;

	// やられ状態にする
	mState = PLAYER_STATE_BOMB;

	// 見た目を爆破状態へ
	mSprite.src.x = 32;
	mSprite.src.y = 80;
	mSprite.size.x = 16;
	mSprite.size.y = 16;

	mSprite.scale.x = 3.0f;
	mSprite.scale.y = 3.0f;
}


/*-------------------------------------------------------
更新
----------------------------------------------------*/
BOOL Player::IsDamage(void)
{
	BOOL res = mState == PLAYER_STATE_BOMB;

	return res;
}