/*
プレイシーン
作成日 : 2020/07/02
作成者 : 米澤駿介
*/
#pragma once

#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "BackGround.h"
#include "UserInterface.h"

struct PlayScene
{
	// 変数 ==================================

	// 状態
	int mState;

	// 画像ハンドル
	int mShootingHandle;		// シューティングハンドル

	// プレイヤー
	Player mPlayer;

	// 弾の管理者
	BulletManager mBulletManage;

	// 敵の管理者
	EnemyManager mEnemyManager;

	// 背景
	BackGround mBackGround;

	UserInterface mUserInterface;
	
	// 関数 ==================================

	// 初期化
	void Initialize();

	// 情報リセット
	void Reset();

	// 更新
	int Update();

	// 描画
	void Draw();

	// 終了処理
	void Finalize();

};
