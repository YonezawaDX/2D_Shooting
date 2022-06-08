/*
ゲーム内の詳細データ
作成日 : 2020/06/28
作成者 : 米澤駿介
*/

#include "Database.h"

const BulletData Database::msBulletDate[BULLET_TYPE_NUM] = {

	//		威力		速度		半径		画像切り取り情報
	{		1,			6.0f,		8.0f,		0,		80,		16,	16,		},		// プレイヤーの通常弾
	{		3,			9.0f,		8.0f,		0,		80,		16,	16,		},		// プレイヤーの強化弾

	{		3,			9.0f,		8.0f,		16,		80,		16,	16,		},		// 敵の通常弾

};

const EnemyData Database::msEnemyData[BULLET_TYPE_NUM] = {

	//		HP			速度		半径		画像切り取り情報				スコア
	{		1,			3.0f,		16.0f,		96,		0,		32,	32,			15},		// 通常
	{		6,			1.0f,		16.0f,		32,		0,		32,	32,			5},		// 隕石

};

const EnemyArrivalData Database::mEnemyArrivalData[ENEMY_ARRIVAL_NUM] = {
	//		出現時間		敵の種類	
	{		60,				ENEMY_TYPE_NORMAL		},
	{		310,			ENEMY_TYPE_METEO		},
	{		320,			ENEMY_TYPE_METEO		},
	{		320,			ENEMY_TYPE_METEO		},
	{		350,			ENEMY_TYPE_NORMAL		},
	{		350,			ENEMY_TYPE_METEO		},
	{		350,			ENEMY_TYPE_NORMAL		},
	{		380,			ENEMY_TYPE_METEO		},
	{		400,			ENEMY_TYPE_METEO		},
	{		400,			ENEMY_TYPE_METEO		},
	{		400,			ENEMY_TYPE_NORMAL		},
	{		500,			ENEMY_TYPE_NORMAL		},
	{		500,			ENEMY_TYPE_NORMAL		},
	{		580,			ENEMY_TYPE_METEO		},
	{		600,			ENEMY_TYPE_METEO		},
	{		600,			ENEMY_TYPE_METEO		},
	{		600,			ENEMY_TYPE_NORMAL		},
	{		650,			ENEMY_TYPE_NORMAL		},
	{		680,			ENEMY_TYPE_NORMAL		},
	{		690,			ENEMY_TYPE_METEO		},
	{		690,			ENEMY_TYPE_METEO		},
	{		700,			ENEMY_TYPE_METEO		},
	{		700,			ENEMY_TYPE_NORMAL		},
	{		700,			ENEMY_TYPE_NORMAL		},
	{		750,			ENEMY_TYPE_NORMAL		},
	{		780,			ENEMY_TYPE_NORMAL		},
	{		800,			ENEMY_TYPE_NORMAL		},
	{		800,			ENEMY_TYPE_NORMAL		},
	{		800,			ENEMY_TYPE_NORMAL		},
	{		820,			ENEMY_TYPE_NORMAL		},
	{		850,			ENEMY_TYPE_NORMAL		},
	{		870,			ENEMY_TYPE_NORMAL		},
	{		900,			ENEMY_TYPE_NORMAL		},
	{		920,			ENEMY_TYPE_NORMAL		},


	
};

