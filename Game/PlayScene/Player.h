/*
タイトルシーン
作成日 : 2020/06/22
作成者 : 米澤駿介
*/
#pragma once

#include "../Utility.h"
#include "BulletManager.h"
#include "Collision.h"

struct Player
{
	// 変数 ====================================

	// 状態
	int mState;

	// 画像描画構造体
	SpriteData mSprite;

	// 座標
	Float2 mPos;

	// 弾の管理者のポインタ (連絡先)
	BulletManager* mpBulletManager;

	// 弾の発射間隔管理用のタイマー
	int mShootIntervalTimer;

	// 当たり判定
	CircleCollider mCollision;

	// 爆発用タイマー
	int mBombTimer;

	// 無敵タイマー
	int mInvTimer;

	// 弾の発射音
	int mBulletSe;

	// 関数 =====================================

	// 初期化
	void Initialize(int textureHandle, BulletManager* pBulletManager);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 移動
	void Move(void);

	// ダメージ処理
	void Damage(void);

	// 被弾中か確認
	BOOL IsDamage(void);
};