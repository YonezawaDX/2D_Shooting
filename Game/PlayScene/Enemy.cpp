#include "Enemy.h"

#include "../GameMain.h"
#include "Database.h"
#include "../GameData.h"
#include <math.h>

// �G�̏��
enum ENEMY_STATE
{
	ENEMY_STATE_ACTIVE,		// �ʏ���
	ENEMY_STATE_BOMB,		// ������
};

// �G�̐����͈�
#define ENEMY_ALIVE_AREA		100


// �J�n���W
#define ENEMY_START				110
#define ENEMY_START_POS_X		(SCREEN_RIGHT - ENEMY_ALIVE_AREA + ENEMY_START)
#define ENEMY_START_POS_Y		(SCREEN_BOTTOM - 50)

// �ʏ�G�̒e���ˊԊu
#define ENEMY_NORMAL_SHOT_INTERVAL		60

// �~����
#define PI						3.141593f
#define COUNT_1					40.0f
#define COUNT_2					4.0f

/*---------------------------------------------------------
������
����		:int textureHandle(�摜�n���h��), int enemyType(���), BulletManager* pBulletManager(�e�̊Ǘ��҂̃|�C���^)
---------------------------------------------------------*/
void Enemy::Initialize(int textureHandle, int enemyType, BulletManager* pBulletManager)
{
	// �e�̎�ނ�ۑ�
	mType = enemyType;

	// �e�̏����擾
	const EnemyData data = Database::msEnemyData[enemyType];

	// �摜�̐ݒ�
	mSprite.SetTexture(textureHandle);
	mSprite.src.x = data.mRectX1;
	mSprite.src.y = data.mRectY1;
	mSprite.size.x = data.mRectX2;
	mSprite.size.y = data.mRectY2;

	mSprite.scale.x = 1.0f;
	mSprite.scale.y = 1.0f;

	// HP�̏�����
	mHp = data.mHp;

	// �������W�̐ݒ�(�c�����̓����_��)
	mPos.y = (float)GetRand(ENEMY_START_POS_Y);
	mPos.x = ENEMY_START_POS_X;

	// �摜�ɍ��W�𔽉f
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// ��Ԃ̏�����
	mState = ENEMY_STATE_ACTIVE;

	// �e�̊Ǘ��҃|�C���^�i�A����j
	mpBulletManager = pBulletManager;

	// �g�p��ԂƂ���
	mIsActive = TRUE;

	// �����蔻��̏�����
	mCollision.mRadius = data.mRadius;
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;

	// �^�C�}�[�̏�����
	mShotTimer = 0;
	mBombTimer = 0;

	// �G�̂��ꉹ
	mBombSe = LoadSoundMem("Resources/Audio/swing34.wav");
}

/*-------------------------------------------------------
�X�V
-----------------------------------------------------*/
void Enemy::Update(void)
{

	// �A�N�e�B�u��ԂłȂ���Ώ������Ȃ�
	if (mIsActive == FALSE)
	{
		return;
	}

	// �G���̎擾
	const EnemyData data = Database::msEnemyData[mType];

	// �G�̎�ނɉ���������
	switch (mType)
	{
		case ENEMY_TYPE_NORMAL:
		{
			// ���ˊԊu�p�^�C�}�[��i�߂�
			++mShotTimer %= ENEMY_NORMAL_SHOT_INTERVAL;

			// ���Ԃ�������e����
			if (mShotTimer == 0)
			{
				mpBulletManager->Shot(BULLET_TYPE_ENEMY_NORMAL, SHOOTER_TYPE_ENEMY, mPos);
			}

			break;
		}

	}
	
	// ��Ԃɉ���������
	switch (mState)
	{
		// �ʏ���
		case ENEMY_STATE_ACTIVE:
		{
			counter++;
			mPos.x -= data.mVel;
			//sin�J�[�u
			mPos.y -= sinf(PI*counter/COUNT_1) * COUNT_2;
			break;
		}

		// ������
		case ENEMY_STATE_BOMB:
		{
			// �^�C�}�[�������߂�
			mBombTimer++;

			// �X�R�A
			g_gameData.mBreakScore += data.mScore;


			if (mBombTimer == 5)
			{

				PlaySoundMem(mBombSe, DX_PLAYTYPE_BACK, TRUE);
				mSprite.src.x = 48;
			}
			else if (mBombTimer == 10)
			{
				mSprite.src.x = 64;
			}
			else if (mBombTimer == 15)
			{
				mSprite.src.x = 80;
			}
			else if (mBombTimer >= 20)
			{
				// ���j���I�������疢�g�p��Ԃɂ���
				mIsActive = FALSE;

				// ���j����1�@���₷
				g_gameData.mBreakNum++;
			}

			break;
		}
	}

	// �����͈͊O�ɏo���疢�g�p��Ԃɂ���
	if (
		mPos.x < SCREEN_LEFT - ENEMY_ALIVE_AREA ||
		mPos.x > SCREEN_RIGHT + ENEMY_ALIVE_AREA ||
		mPos.y < SCREEN_TOP - ENEMY_ALIVE_AREA ||
		mPos.y > SCREEN_BOTTOM + ENEMY_ALIVE_AREA
		)
	{
		mIsActive = FALSE;
	}

	// �摜�ɍ��W�𔽉f
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// �����蔻��ɍ��W���X�V
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;
}

/*--------------------------------------------------
�`��
---------------------------------------------------*/
void Enemy::Draw(void)
{
	// �A�N�e�B�u��ԂłȂ���Ώ������Ȃ�
	if (mIsActive == FALSE)
	{
		return;
	}

	mSprite.Draw();
}

/*-------------------------------------------------
�_���[�W����
--------------------------------------------------*/
void Enemy::Damage(int damage)
{
	// �̗͂����
	mHp -= damage;

	// �̗͂��Ȃ��Ȃ��Ă����甚�j��Ԃ�
	if (mHp <= 0)
	{
		mState = ENEMY_STATE_BOMB;

		// �����ڂ𔚔j��Ԃ�
		mSprite.src.x = 32;
		mSprite.src.y = 80;
		mSprite.size.x = 16;
		mSprite.size.y = 16;

		mSprite.scale.x = 3.0f;
		mSprite.scale.y = 3.0f;
	}
}
