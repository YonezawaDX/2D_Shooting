/*
タイトルシーン
作成日 : 2020/06/20
作成者 : 米澤駿介
*/
#pragma once

struct TitleScene
{
	// 変数 ====================================

	// 状態
	int mState;

	// タイマー
	int mTimer;

	// 文字の切り替えフラグ
	int mIsDrawString;

	// サウンドハンドル
	int mKeySe;

	// タイトルBGM
	int TitleBGM;

	// 画像ハンドル
	int mBackgroundTexture;

	// ロゴハンドル
	int mMovieTitle;

	// 画像情報
	SpriteData mSprite;

	// 関数 =====================================

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