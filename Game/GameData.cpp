#include "GameData.h"

GameData g_gameData;


/*----------------------------------------------
初期化
----------------------------------------------*/
void GameData::Initialize(void)
{
	// 撃破数の初期化
	mBreakNum = 0;

	// スコアの初期化
	mBreakScore = 0;

	mStock = 2;
}