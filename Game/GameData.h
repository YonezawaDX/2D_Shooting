/*
ゲームデータ
作成日 : 2020/06/04
作成者 : 米澤駿介
*/
#pragma once

struct GameData
{
	// 変数 ===================================

	// 敵を倒した数
	int mBreakNum;

	// 敵の得点
	int mBreakScore;

	// 残機
	int mStock;

	// 関数 ===================================

	// 初期化
	void Initialize(void);
};

// どこでも使えるようにする
extern GameData g_gameData;
