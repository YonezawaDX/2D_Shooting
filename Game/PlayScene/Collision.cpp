/*
当たり判定構造体
作成日 : 2020/07/02
作成者 : 米澤駿介
*/
#include "Collision.h"

/*-----------------------------------------------
他の円との当たり判定
-------------------------------------------------*/
BOOL CircleCollider::CheckHit(CircleCollider collider)
{
	// 2点の位置を原点からのベクトルにする
	float x = collider.mPos.x - mPos.x;
	float y = collider.mPos.y - mPos.y;

	// ベクトルの長さを計算
	float l = (x * x) + (y * y);

	// 半径の合計を取得
	float circleLen = mRadius + collider.mRadius;

	// 半径の合計を2乗する(sqrtは処理が重いので使わないための処置)
	circleLen *= circleLen;

	// ベクトルが2つの円の半径より短ければ当たっている
	if (l <= circleLen)
	{
		return TRUE;
	}

	return FALSE;
}
