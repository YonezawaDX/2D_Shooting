/*
プレイヤー
作成日 : 2020/06/04
作成者 : 米澤駿介
*/
#pragma once

#include "../Utility.h"
#include "BulletManager.h"
#include "Collision.h"

struct Enemy
{
	// 変数 ============================

	// 敵の種類
	int mType;

	// 状態
	int mState;

	// HP
	int mHp;

	// 画像情報
	SpriteData mSprite;

	// 座標
	Float2 mPos;

	// 速度
	Float2 mVel;

	// 使用されているかのフラグ
	BOOL mIsActive;

	// 弾の管理者のポインタ（連絡先）
	BulletManager* mpBulletManager;

	// 当たり判定情報
	CircleCollider mCollision;

	// 弾発射用のタイマー
	int mShotTimer;

	// 爆破処理用のタイマー
	int mBombTimer;

	// 敵のやられ音
	int mBombSe;

	// カウンター
	int counter;

	// 関数 ==================================

	// 初期化
	void Initialize(int textureHandle, int enemyType, BulletManager* pBulletManager);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// ダメージ処理
	void Damage(int damage);
};