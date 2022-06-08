/*
弾の処理
作成日 : 2020/07/14
作成者 : 米澤駿介
*/
#include "Bullet.h"

#include "../GameMain.h"

// 弾が生存している画面外プラスαの範囲
#define BULLET_ALIVE_AREA		50

/*---------------------------------------------
初期化
引数	: int textureHandle(弾の画像ハンドル), int bulletType(弾の種類),Float2 pos
----------------------------------------------*/
void Bullet::Initialize(int textureHandle, int bulletType, int shooterType, Float2 pos)
{
	// 弾の種類を保存
	mBulletType = bulletType;

	// 発射対象の保存
	mShooterType = shooterType;

	// 弾の情報を取得
	const BulletData data = Database::msBulletDate[bulletType];

	//画像の設定
	mSprite.SetTexture(textureHandle);
	mSprite.src.x = data.mRectX1;
	mSprite.src.y = data.mRectY1;
	mSprite.size.x = data.mRectX2;
	mSprite.size.y = data.mRectY2;

	// 初期座標の設定
	mPos.x = pos.x;
	mPos.y = pos.y;

	// 画像に座標を反映
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// 使用状態とする
	mIsActive = TRUE;

	// 威力の設定
	mPower = data.mPower;

	// 当たり判定情報の初期化
	mCollision.mRadius = data.mRadius;
	mCollision.mPos.x = pos.x;
	mCollision.mPos.y = pos.y;
}

/*----------------------------------------------
更新
-----------------------------------------------*/
void Bullet::Update(void)
{
	// 使用中でなければ処理しない
	if (mIsActive == FALSE)
	{
		return;
	}

	// 弾の情報を取得
	const BulletData data = Database::msBulletDate[mBulletType];

	// 弾の種類に応じた移動処理
	switch (mBulletType)
	{
		case BULLET_TYPE_PLAYER_NORMAL:		// プレイヤー通常弾
		case BULLET_TYPE_PLAYER_POWER:		// プレイヤー強化弾
		{
			mPos.x += data.mVel;
			break;
		}

		case BULLET_TYPE_ENEMY_NORMAL:		// 敵の通常弾
		{
			mPos.x -= data.mVel;
			break;
		}

	}

	// 画面外に出たら弾を未使用状態にする
	if (
		mPos.x < SCREEN_LEFT - BULLET_ALIVE_AREA ||
		mPos.x > SCREEN_RIGHT + BULLET_ALIVE_AREA ||
		mPos.y < SCREEN_TOP - BULLET_ALIVE_AREA ||
		mPos.y > SCREEN_BOTTOM + BULLET_ALIVE_AREA
		)
	{
		mIsActive = FALSE;
	}

	// 画像に座標を反映
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// 当たり判定に座標を反映
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;
}

/*----------------------------------------------------
描画
----------------------------------------------------*/
void Bullet::Draw(void)
{
	// 使用中でなければ処理しない
	if (mIsActive == FALSE)
	{
		return;
	}

	// 自機の表示
	mSprite.Draw();
}