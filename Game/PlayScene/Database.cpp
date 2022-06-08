/*
�Q�[�����̏ڍ׃f�[�^
�쐬�� : 2020/06/28
�쐬�� : ���V�x��
*/

#include "Database.h"

const BulletData Database::msBulletDate[BULLET_TYPE_NUM] = {

	//		�З�		���x		���a		�摜�؂�����
	{		1,			6.0f,		8.0f,		0,		80,		16,	16,		},		// �v���C���[�̒ʏ�e
	{		3,			9.0f,		8.0f,		0,		80,		16,	16,		},		// �v���C���[�̋����e

	{		3,			9.0f,		8.0f,		16,		80,		16,	16,		},		// �G�̒ʏ�e

};

const EnemyData Database::msEnemyData[BULLET_TYPE_NUM] = {

	//		HP			���x		���a		�摜�؂�����				�X�R�A
	{		1,			3.0f,		16.0f,		96,		0,		32,	32,			15},		// �ʏ�
	{		6,			1.0f,		16.0f,		32,		0,		32,	32,			5},		// 覐�

};

const EnemyArrivalData Database::mEnemyArrivalData[ENEMY_ARRIVAL_NUM] = {
	//		�o������		�G�̎��	
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

