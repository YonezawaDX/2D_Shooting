/*
�Q�[�����̏ڍ׃f�[�^
�쐬�� : 2020/06/28
�쐬�� : ���V�x��
*/
#pragma once

#include "../Utility.h"
#include "../GameData.h"

// �e�̎��
enum BULLET_TYPE
{
	BULLET_TYPE_PLAYER_NORMAL,		// �v���C���[�̒ʏ�e
	BULLET_TYPE_PLAYER_POWER,		// �v���C���[�̋����e

	BULLET_TYPE_ENEMY_NORMAL,		// �G�̒ʏ�e
	BULLET_TYPE_ENEMY_BOS,			// �����e
	// ��ނ̐�
	BULLET_TYPE_NUM
};

// �e�̏��
struct BulletData
{
	// �З�
	int mPower;

	// �ړ����x
	float mVel;

	// �����蔻��̔��a
	float mRadius;

	// �摜�̐؂�����
	int mRectX1;
	int mRectY1;
	int mRectX2;
	int mRectY2;
};


// �G�̎��
enum ENEMY_TYPE
{
	ENEMY_TYPE_NORMAL,		// �ʏ�
	ENEMY_TYPE_METEO,		// 覐�
	ENEMY_TYPE_BOS,			// ����

	// ��ނ̐�
	ENEMY_TYPE_NUM
};

// �G�̏��
struct EnemyData
{
	// HP
	int mHp;

	// �ړ����x
	float mVel;

	// �����蔼�a�̔��a
	float mRadius;

	// �摜�̐؂�����
	int mRectX1;
	int mRectY1;
	int mRectX2;
	int mRectY2;

	// �X�R�A
	int mScore;
};



// �G�̍ő�o����
#define ENEMY_ARRIVAL_NUM		128

// �G�̏o�����
struct EnemyArrivalData
{
	// �o������
	int mArrivalTime;

	// �o������G�̎��
	int mEnemyType;

};

// �f�[�^���܂Ƃ߂��\����
struct Database
{
	// �e�̎��
	static const BulletData msBulletDate[BULLET_TYPE_NUM];

	// �G�̎��
	static const EnemyData msEnemyData[BULLET_TYPE_NUM];

	// �G�̏o���p�^�[��
	static const EnemyArrivalData mEnemyArrivalData[ENEMY_ARRIVAL_NUM];
};