/*
ゲーム内の詳細データ
作成日 : 2020/06/28
作成者 : 米澤駿介
*/
#pragma once

#include "../Utility.h"
#include "../GameData.h"

// 弾の種類
enum BULLET_TYPE
{
	BULLET_TYPE_PLAYER_NORMAL,		// プレイヤーの通常弾
	BULLET_TYPE_PLAYER_POWER,		// プレイヤーの強化弾

	BULLET_TYPE_ENEMY_NORMAL,		// 敵の通常弾
	BULLET_TYPE_ENEMY_BOS,			// 強い弾
	// 種類の数
	BULLET_TYPE_NUM
};

// 弾の情報
struct BulletData
{
	// 威力
	int mPower;

	// 移動速度
	float mVel;

	// 当たり判定の半径
	float mRadius;

	// 画像の切り取り情報
	int mRectX1;
	int mRectY1;
	int mRectX2;
	int mRectY2;
};


// 敵の種類
enum ENEMY_TYPE
{
	ENEMY_TYPE_NORMAL,		// 通常
	ENEMY_TYPE_METEO,		// 隕石
	ENEMY_TYPE_BOS,			// 強い

	// 種類の数
	ENEMY_TYPE_NUM
};

// 敵の情報
struct EnemyData
{
	// HP
	int mHp;

	// 移動速度
	float mVel;

	// 当たり半径の半径
	float mRadius;

	// 画像の切り取り情報
	int mRectX1;
	int mRectY1;
	int mRectX2;
	int mRectY2;

	// スコア
	int mScore;
};



// 敵の最大出現数
#define ENEMY_ARRIVAL_NUM		128

// 敵の出現情報
struct EnemyArrivalData
{
	// 出現時間
	int mArrivalTime;

	// 出現する敵の種類
	int mEnemyType;

};

// データをまとめた構造体
struct Database
{
	// 弾の種類
	static const BulletData msBulletDate[BULLET_TYPE_NUM];

	// 敵の種類
	static const EnemyData msEnemyData[BULLET_TYPE_NUM];

	// 敵の出現パターン
	static const EnemyArrivalData mEnemyArrivalData[ENEMY_ARRIVAL_NUM];
};