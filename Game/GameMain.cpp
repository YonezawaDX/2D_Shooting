//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付		2020.07.07
//!
//! @author 制作者名	米澤駿介
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"

#include "TitleScene/TitleScene.h"
#include "PlayScene/PlayScene.h"
#include "ResultScene/ResultScene.h"


// 定数の定義 ==============================================================



// グローバル変数の定義 ====================================================

// シーン
int g_scene = GAME_SCENE_TITLE;

// シーン構造体
TitleScene g_titleScene;		// タイトル	
PlayScene g_playScene;			// プレイ
ResultScene g_resultScene;


// 関数の宣言 ==============================================================
// <ゲーム> ------------------------------------------------------------
void InitializeGame(void);  // ゲームの初期化処理
void UpdateGame(void);      // ゲームの更新処理
void RenderGame(void);      // ゲームの描画処理
void FinalizeGame(void);    // ゲームの終了処理



// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{
	g_titleScene.Initialize();
	g_playScene.Initialize();
	g_resultScene.Initialize();
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	int nextScene = GAME_SCENE_NONE;

	switch (g_scene)
	{
		// タイトルシーン ===============================================
		case GAME_SCENE_TITLE:
		{
			nextScene = g_titleScene.Update();

			break;
		}
		// プレイシーン　============================================
		case GAME_SCENE_PLAY:
		{
			nextScene = g_playScene.Update();

			break;
		}
		// リザルトシーン　============================================
		case GAME_SCENE_RESULT:
		{
			nextScene = g_resultScene.Update();

			break;
		}

		// 例外
		default:
		{
			break;
		}
	}
		// 次のシーンがあれば変更
	if (nextScene != GAME_SCENE_NONE)
	{
		g_scene = nextScene;
	}
}




//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{
		switch (g_scene)
		{
			// タイトルシーン ===============================================
			case GAME_SCENE_TITLE:
			{
				g_titleScene.Draw();

				break;
			}
			// プレイシーン　============================================
			case GAME_SCENE_PLAY:
			{
				g_playScene.Draw();

				break;
			}
			// リザルトシーン　============================================
			case GAME_SCENE_RESULT:
			{
				g_resultScene.Draw();
				break;
			}

			// 例外
			default:
			{
				break;
			}
		}

	// フェードの描画
	FadeDraw(GetColor(0, 0, 0));
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	g_titleScene.Finalize();
	g_playScene.Finalize();
	g_resultScene.Finalize();
}
