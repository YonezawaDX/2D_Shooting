#include "ResultScene.h"

#include "../GameMain.h"
#include "../GameData.h"

//  シーンの状態
enum RESULT_STATE
{
	RESULT_STATE_INITIALIZE,		// 初期化

	RESULT_STATE_FADEIN,			// フェードイン待ちの状態
	RESULT_STATE_MAIN,				// メイン処理
	RESULT_STATE_FADEOUT,			// フェードアウト状態

	RESULT_STATE_FINALIZE,			// 終了処理

};

// リザルト文字の座標
#define RESULT_LOGO_POS_X			(SCREEN_CENTER_X - 100)
#define RESULT_LOGO_POS_Y			(SCREEN_CENTER_Y - 100)

// リザルト文字のサイズ
#define RESULT_LOGO_SIZE			50

// 結果文字の座標
#define RESULT_POS_X				(SCREEN_CENTER_X - 100)
#define RESULT_POS_Y				(SCREEN_CENTER_Y + 100)

// 結果文字のサイズ
#define RESULT_SIZE					30

// 残機の文字の座標
#define RE_POS_Y					(RESULT_LOGO_POS_Y + 70)

/*------------------------------------------------
初期化
-------------------------------------------------*/
void ResultScene::Initialize(void)
{
	mKeySe = LoadSoundMem("Resources/Audio/SE00.ogg");
	
	// 変数などのリセット
	Reset();
}

/*------------------------------------------------
情報のリセット
----------------------------------------------------*/
void ResultScene::Reset(void)
{
	// 状態の初期化
	mState = RESULT_STATE_INITIALIZE;
}

/*-----------------------------------------------------
更新
------------------------------------------------------*/
int ResultScene::Update(void)
{
	int nextScene = GAME_SCENE_NONE;

	switch (mState)
	{
		// 初期化       ==================================
		case RESULT_STATE_INITIALIZE:
		{
			// 変数などのリセット
			Reset();

			// フェードイン状態へ
			mState = RESULT_STATE_FADEIN;

			// フェードアウト済みの状態にする
			SetFadeOut();

			break;
		}
		// フェードイン		===============================
		case  RESULT_STATE_FADEIN:
		{
			// フェードの更新
			int res = FadeInUpdate(FADE_TIME);

			// フェードが終了したら次の状態へ
			if (res == FALSE)
			{
				mState = RESULT_STATE_MAIN;
			}

			break;
		}
		// メイン処理		================================
		case RESULT_STATE_MAIN:
		{
			// ボタンが押さえたら次へ
			if (IsButtonPressed(PAD_INPUT_1) == TRUE)
			{
				// 決定音
				PlaySoundMem(mKeySe, DX_PLAYTYPE_BACK);

				mState = RESULT_STATE_FADEOUT;
			}

			break;
		}
		// フェードアウト		===================================
		case RESULT_STATE_FADEOUT:
		{
			// フェードの更新
			int res = FadeOutUpdate(FADE_TIME);

			// フェードが終了したら次の状態へ
			if (res == FALSE)
			{
				mState = RESULT_STATE_FINALIZE;
			}

			break;
		}
		// 終了処理			===========================
		case RESULT_STATE_FINALIZE:
		{
			// 次のシーンへ
			nextScene = GAME_SCENE_TITLE;

			// 変数などのリセット
			Reset();

			break;
		}
	}

	return nextScene;
}

/*-------------------------------------------------
描画
--------------------------------------------------*/
void ResultScene::Draw(void)
{
	int defaultSize = GetFontSize();

	// リザルト文字の表示

	SetFontSize(RESULT_LOGO_SIZE);

	DrawFormatString(
		RESULT_LOGO_POS_X,
		RESULT_LOGO_POS_Y,
		GetColor(255, 255, 0),
		"リザルト"
	);

	// スコアの表示
	SetFontSize(RESULT_SIZE);

	DrawFormatString(
		RESULT_POS_X,
		RESULT_POS_Y,
		GetColor(255, 255, 0),
		"スコア : %d",
		g_gameData.mBreakScore
	);

	// 残機の表示
	DrawFormatString(
		RESULT_POS_X,
		RE_POS_Y,
		GetColor(255, 255, 0),
		" 残機 : %d",
		g_gameData.mStock
	);



	SetFontSize(defaultSize);
}

/*-------------------------------------------------------------
終了処理
--------------------------------------------------*/
void ResultScene::Finalize(void)
{
}
