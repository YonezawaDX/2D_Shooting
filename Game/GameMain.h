//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム全体に関するヘッダファイル
//!
//! @date   日付		2020.06.16
//!
//! @author 制作者名	米澤駿介
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once



// 定数の定義 ==============================================================
// <システム> ----------------------------------------------------------
#define GAME_TITLE "Sample Game"        // ゲームタイトル


// <画面> --------------------------------------------------------------
#define SCREEN_WIDTH    (640)                  // 画面の幅[pixel]
#define SCREEN_HEIGHT   (480)                  // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

// <シーン> -------------------------------------------------------------
enum GAME_SCENE
{
	GAME_SCENE_NONE,	// なし

	GAME_SCENE_TITLE,	// タイトル
	GAME_SCENE_PLAY,	// プレイ
	GAME_SCENE_RESULT,	// リザルト
};


// フェードインの時間
#define FADE_TIME		0.5f




// 関数の宣言 ==============================================================
// <ゲーム> ------------------------------------------------------------
void InitializeGame(void);    // ゲームの初期化処理
void UpdateGame(void);        // ゲームの更新処理
void RenderGame(void);        // ゲームの描画処理
void FinalizeGame(void);      // ゲームの終了処理
