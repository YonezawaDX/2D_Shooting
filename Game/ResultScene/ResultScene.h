/*
リザルトシーン
作成日 : 2020/07/06
作成者 : 米澤駿介
*/
#pragma once

struct ResultScene
{
	// 変数 ======================================
	
	// 状態
	int mState;

	// サウンドハンドル
	int mKeySe;

	// 関数 =======================================

	// 初期化
	void Initialize(void);

	// 情報リセット
	void Reset(void);

	// 更新
	int Update(void);

	// 描画
	void Draw(void);

	// 終了処理
	void Finalize(void);

};