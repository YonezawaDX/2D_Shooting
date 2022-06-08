/*
�v���C���[
�쐬�� : 2020/06/23
�쐬�� : ���V�x��
*/
#include <math.h>

#include "Player.h"

#include "../GameMain.h"


// �v���C���[�̏��
enum PLAYER_STATE
{
	PLAYER_STATE_ACTIVE,		// ����ł�����
	PLAYER_STATE_BOMB,			// ������
};

// ��s�@�̉摜�̐؂�����
#define PLAYER_RECT_X1			0
#define PLAYER_RECT_Y1			0
#define PLAYER_RECT_X2			32
#define PLAYER_RECT_Y2			32

// ��s�@�~�j�摜
#define PLAYER_MINI_X1			192
#define PLAYER_MINI_Y1			0
#define PLAYER_MINI_X2			60
#define PLAYER_MINI_Y2			32

// �ړ��X�s�[�h
#define PLAYER_VEL				5.0f

// �e�̔��ˊԊu
#define PLAYER_BULLET_INTERVAL		5

// �����̎c�@
#define PLAYER_STOCK_DEFAULT		2

// �v���C���[�̓����蔻��
#define PLAYER_RADIUS				8.0f

/*----------------------------------------------------
������
----------------------------------------------------*/
void Player::Initialize(int textureHandle, BulletManager* pBulletManager)
{
	// ��Ԃ̏�����
	mState = PLAYER_STATE_ACTIVE;

	// �摜�̐ݒ�
	mSprite.SetTexture(textureHandle);
	mSprite.src.x = PLAYER_RECT_X1;
	mSprite.src.y = PLAYER_RECT_Y1;
	mSprite.size.x = PLAYER_RECT_X2;
	mSprite.size.y = PLAYER_RECT_Y2;

	mSprite.scale.x = 1.0f;
	mSprite.scale.y = 1.0f;

	mSprite.alpha = 1.0f;

	// �������W�̐ݒ�
	mPos.x = SCREEN_CENTER_X;
	mPos.y = SCREEN_CENTER_Y;

	// �摜�ɍ��W�𔽉f
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// �e�̊Ǘ��҂̃|�C���^ (�A����) ��ۑ�
	mpBulletManager = pBulletManager;

	// �e�̔��ˊԊu�Ǘ��p�^�C�}�[�̏�����
	mShootIntervalTimer = 0;

	// �����蔻��̏�����
	mCollision.mRadius = PLAYER_RADIUS;
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;

	// �e�̉�
	mBulletSe = LoadSoundMem("Resources/Audio/pi77.wav");
}

/*----------------------------------------------------
�X�V
-----------------------------------------------------*/
void Player::Update(void)
{
	switch (mState)
	{
		// ����ł�����		=========================
		case PLAYER_STATE_ACTIVE:
		{
			// �^�C�}�[����
			++mShootIntervalTimer %= PLAYER_BULLET_INTERVAL;

			// �ړ�����
			Move();

			// �e�̔��ˏ���
			if (mShootIntervalTimer == 0 && IsButtonDown(PAD_INPUT_1) == TRUE)
			{
				mpBulletManager->Shot(BULLET_TYPE_PLAYER_POWER, SHOOTER_TYPE_PLAYER, mPos);

				// �e�̉�
				PlaySoundMem(mBulletSe, DX_PLAYTYPE_BACK, TRUE);

			}

			break;
		}
		// ������        =======================================
		case PLAYER_STATE_BOMB:
		{
			// �^�C�}�[��i�߂�
			mBombTimer++;

			if (mBombTimer == 5)
			{
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
			else if(mBombTimer == 20)
			{
				mSprite.alpha = 0.0f;
			}
			else if (mBombTimer >= 60)
			{
				// ���j���I�������畜�A������
				mSprite.src.x = PLAYER_MINI_X1;
				mSprite.src.y = PLAYER_MINI_Y1;
				mSprite.size.x = PLAYER_MINI_X2;
				mSprite.size.y = PLAYER_MINI_Y2;


				mSprite.scale.x = 0.8f;
				mSprite.scale.y = 0.8f;

				mSprite.alpha = 1.0f;

				// �����^�C�}�[�̏�����
				mBombTimer = 0;

				// ����\��Ԃ�
				mState = PLAYER_STATE_ACTIVE;
			}

			break;
		}
	}

	// �摜�ɍ��W�𔽉f
	mSprite.pos.x = mPos.x;
	mSprite.pos.y = mPos.y;

	// �����蔻��ɍ��W�𔽉f
	mCollision.mPos.x = mPos.x;
	mCollision.mPos.y = mPos.y;
}

/*-------------------------------------------------
�`��
-------------------------------------------------*/
void Player::Draw(void)
{
	//���@�̕\��
	mSprite.Draw();
}

/*-----------------------------------------------------------------
�v���C���[�̈ړ�����
-------------------------------------------------------*/
void Player::Move(void)
{
	// �ړ�
	int inputUD = 0;
	int inputLR = 0;

	// �㉺
	if (IsButtonDown(PAD_INPUT_UP) == TRUE)
	{
		inputUD = -1;
	}

	if (IsButtonDown(PAD_INPUT_DOWN) == TRUE)
	{
		inputUD = 1;
	}

	// ���E
	if (IsButtonDown(PAD_INPUT_LEFT) == TRUE)
	{
		inputLR = -1;
	}

	if (IsButtonDown(PAD_INPUT_RIGHT) == TRUE)
	{
		inputLR = 1;
	}

	// ���͂�����Ă��Ȃ��Ȃ炱��ȏ㏈�����Ȃ�
	if (inputUD == 0 && inputLR == 0)
	{
		// �������^�[��
		return;
	}

	// ���͏����x�N�g���v�Z�p��flort�^�֕ϊ�
	float vx = (float)inputLR;
	float vy = (float)inputUD;

	// �x�N�g���̒������擾
	float vl = sqrtf((vx * vx) + (vy * vy));

	// �P�ʃx�N�g���i������1�̃x�N�g���j���v�Z
	vx /= vl;
	vy /= vl;

	// �ړ��x�N�g����ړI�̑傫���i�ړ��ʁj�ɃX�P�[�����O
	vx *= PLAYER_VEL;
	vy *= PLAYER_VEL;

	// �ړ��ʂ����W�ɉ��Z
	mPos.x += vx;
	mPos.y += vy;

	// ���W�̈ړ�����
	mPos.x = ClampF(mPos.x, SCREEN_LEFT, SCREEN_RIGHT);
	mPos.y = ClampF(mPos.y, SCREEN_TOP, SCREEN_BOTTOM);
}

/*----------------------------------------------------
�_���[�W����
------------------------------------------------------*/
void Player::Damage(void)
{
	// �c�@��1���炷
	g_gameData.mStock--;

	// �����Ԃɂ���
	mState = PLAYER_STATE_BOMB;

	// �����ڂ𔚔j��Ԃ�
	mSprite.src.x = 32;
	mSprite.src.y = 80;
	mSprite.size.x = 16;
	mSprite.size.y = 16;

	mSprite.scale.x = 3.0f;
	mSprite.scale.y = 3.0f;
}


/*-------------------------------------------------------
�X�V
----------------------------------------------------*/
BOOL Player::IsDamage(void)
{
	BOOL res = mState == PLAYER_STATE_BOMB;

	return res;
}