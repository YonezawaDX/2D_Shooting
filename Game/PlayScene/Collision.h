/*
当たり判定構造体
作成日 : 2020/07/02
作成者 : 米澤駿介
*/
#pragma once

#include "../Utility.h"

// 円の判定用構造体
struct CircleCollider
{
	// 変数 ===================================

	// 半径
	float mRadius;

	// 座標
	Float2 mPos;

	// 関数 ====================================

	// 他の円との当たり判定
	BOOL CheckHit(CircleCollider collider);
};