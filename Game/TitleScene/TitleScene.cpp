#include "TitleScene.h"

#include "../GameMain.h"


// シーンの状態
enum  TITLE_STATE
{
	TITLE_STATE_INITIALIZE,		// 初期化

	TITLE_STATE_FADEIN,			// フェードイン待ちの状態
	TITLE_STATE_MAIN,			// メイン処理
	TITLE_STATE_FADEOUT,		// フェードアウト状態

	TITLE_STATE_FINALIZE,		//終了処理
};

// タイトル座標
#define TITLE_POS_X			(SCREEN_CENTER_X - 220)
#define TITLE_POS_Y			(SCREEN_CENTER_Y - 80)

// タイトルロゴサイズ
#define TITLE_LOGO_SIZE			60

// キー入力の文字位置
#define PUSHKEY_POS_X		(SCREEN_CENTER_X - 40)
#define PUSHKEY_POS_Y		(SCREEN_CENTER_Y + 40)

// キー入力の文字点滅間隔
#define PUSHKEY_INTERVAL	30

/*---------------------------------------------------
初期化
---------------------------------------------------*/
void TitleScene::Initialize(void)
{
	// 決定音
	mKeySe = LoadSoundMem("Resources/Audio/SE00.ogg");
	
	// タイトルの背景
	mBackgroundTexture = LoadGraph("Resources/Textures/back_sky_n02.png");
	
	// ロゴの表示
	mMovieTitle = PlayMovie("Resources/Textures/Movie.avi",1,DX_MOVIEPLAYTYPE_BCANCEL);

	// タイトルBGM
	TitleBGM = LoadSoundMem("Resources/Audio/title.mp3");
	
	// 変数などのリセット
	Reset();
}

/*--------------------------------------------------
情報のリセット
---------------------------------------------------*/
void TitleScene::Reset(void)
{
	// 状態の初期化
	mState = TITLE_STATE_INITIALIZE;

	// タイマーの初期化
	mTimer = 0;

	// フラグの初期化
	mIsDrawString = FALSE;

	// 画像情報の設定
	mSprite.SetTexture(mBackgroundTexture);
	mSprite.pos.x = 320;
	mSprite.pos.y = 240;
	mSprite.scale.x = 2.0f;
	mSprite.scale.y = 2.0f;
}

/*----------------------------------------------------
更新
----------------------------------------------------*/
int TitleScene::Update(void)
{
	int nextScene = GAME_SCENE_NONE;

	switch (mState)
	{
		// 初期化			===============================
		case TITLE_STATE_INITIALIZE:
		{
			// 変数などのリセット
			Reset();

			// フェードイン状態へ
			mState = TITLE_STATE_FADEIN;

			// フェードアウト済みの状態にする
			SetFadeOut();

			break;
		}
		// フェードイン		===============================
		case TITLE_STATE_FADEIN:
		{
			// フェードインの更新
			int res = FadeInUpdate(FADE_TIME);

			// フェードが終了したら次の状態へ
			if (res == FALSE)
			{
				mState = TITLE_STATE_MAIN;
			}

			break;
		}
		// メイン処理		==============================
		case TITLE_STATE_MAIN:
		{
			
			// タイマーを進める
			++mTimer %= PUSHKEY_INTERVAL;

			PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
			// 文字の表示フラグを切り替える
			if (mTimer == 0)
			{
				mIsDrawString = !mIsDrawString;
			}

			// ボタンが押されたら次へ
			if (IsButtonPressed(PAD_INPUT_1) == TRUE)
			{
				// 決定音
				PlaySoundMem(mKeySe, DX_PLAYTYPE_BACK);

				mState = TITLE_STATE_FADEOUT;
			}

			break;
		}
		// フェードアウト	=============================-
		case TITLE_STATE_FADEOUT:
		{
			// フェードの更新
			int res = FadeOutUpdate(FADE_TIME);

			//フェードが終了したら次の状態へ
			if (res == FALSE)
			{
				mState = TITLE_STATE_FINALIZE;
			}

			break;
		}
		// 終了処理			===============================
		case TITLE_STATE_FINALIZE:
		{
			// 次のシーンへ
			nextScene = GAME_SCENE_PLAY;

			// 変数などのリセット
			Reset();

			break;
		}	
	}

	return nextScene;
}

/*------------------------------------------------
描画
------------------------------------------------*/
void TitleScene::Draw(void)
{
	// タイトル背景の表示
	mSprite.Draw();

	// タイトルロゴの表示
	int defaultSize = GetFontSize();

	SetFontSize(TITLE_LOGO_SIZE);

	DrawFormatString(
		TITLE_POS_X,
		TITLE_POS_Y,
		GetColor(255, 255, 0),
		"シューティング"
	);

	SetFontSize(defaultSize);

	// キー入力を促す文字の表示
	if (mIsDrawString == TRUE)
	{
		DrawFormatString(
			PUSHKEY_POS_X,
			PUSHKEY_POS_Y,
			GetColor(255, 255, 0),
			"Push 1 Key"
		);
	}
}

/*------------------------------------------------------
終了処理
-------------------------------------------------------*/
void TitleScene::Finalize(void)
{
	DeleteSoundMem(mKeySe);
	DeleteGraph(mMovieTitle);

}