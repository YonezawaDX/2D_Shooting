/*
�e�̏���
�쐬�� : 2020/07/14
�쐬�� : ���V�x��
*/
#include "Bullet.h"

#include "../GameMain.h"

// �e���������Ă����ʊO�v���X���͈̔�
#define BULLET_ALIVE_AREA		50

/*---------------------------------------------
������
����	: int textureHandle(�e�̉摜�n���h��), int bulletType(�e�̎��),Float2 pos
----------------------------------------------*/
void Bullet::Initialize(int textureHandle, int bulletType, int shooterType, Float2 pos)
{
	// �e�̎�ނ�ۑ�
	mBulletType = bulletType;

	// ���ˑΏۂ̕ۑ�
	mShooterType = shooterType;

	// �e�̏����擾
	const BulletData data = Database::msBulletDate[bulletType];

	//�摜�̐ݒ�
	mSprite.SetTexture(textureHandle);
	mSprite.src.x = data.mRectX1;
	mSprite.src.y = data.mRectY1;
	mSprite.size.x = data.mRectX2;
	mSprite.size.y = data.mRectY2;

	// �������W�̐ݒ�
	mPos.x = pos.x;
	mPos.y = pos.y;

	// �摜�ɍ��W�𔽉f
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// �g�p��ԂƂ���
	mIsActive = TRUE;

	// �З͂̐ݒ�
	mPower = data.mPower;

	// �����蔻����̏�����
	mCollision.mRadius = data.mRadius;
	mCollision.mPos.x = pos.x;
	mCollision.mPos.y = pos.y;
}

/*----------------------------------------------
�X�V
-----------------------------------------------*/
void Bullet::Update(void)
{
	// �g�p���łȂ���Ώ������Ȃ�
	if (mIsActive == FALSE)
	{
		return;
	}

	// �e�̏����擾
	const BulletData data = Database::msBulletDate[mBulletType];

	// �e�̎�ނɉ������ړ�����
	switch (mBulletType)
	{
		case BULLET_TYPE_PLAYER_NORMAL:		// �v���C���[�ʏ�e
		case BULLET_TYPE_PLAYER_POWER:		// �v���C���[�����e
		{
			mPos.x += data.mVel;
			break;
		}

		case BULLET_TYPE_ENEMY_NORMAL:		// �G�̒ʏ�e
		{
			mPos.x -= data.mVel;
			break;
		}

	}

	// ��ʊO�ɏo����e�𖢎g�p��Ԃɂ���
	if (
		mPos.x < SCREEN_LEFT - BULLET_ALIVE_AREA ||
		mPos.x > SCREEN_RIGHT + BULLET_ALIVE_AREA ||
		mPos.y < SCREEN_TOP - BULLET_ALIVE_AREA ||
		mPos.y > SCREEN_BOTTOM + BULLET_ALIVE_AREA
		)
	{
		mIsActive = FALSE;
	}

	// �摜�ɍ��W�𔽉f
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// �����蔻��ɍ��W�𔽉f
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;
}

/*----------------------------------------------------
�`��
----------------------------------------------------*/
void Bullet::Draw(void)
{
	// �g�p���łȂ���Ώ������Ȃ�
	if (mIsActive == FALSE)
	{
		return;
	}

	// ���@�̕\��
	mSprite.Draw();
}