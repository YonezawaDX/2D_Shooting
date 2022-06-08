#include "PlayScene.h"

#include "../GameMain.h"
#include "../GameData.h"

// �V�[���̏��
enum PLAY_STATE
{
	PLAY_STATE_INITIALIZE,		// ������

	PLAY_STATE_FADEIN,			// �t�F�[�h�C���҂��̏��
	PLAY_STATE_MAIN,			// ���C������
	PLAY_STATE_FADEOUT,			// �t�F�[�h�A�E�g���

	PLAY_STATE_FINALIZE,		// �I������

};

/*------------------------------------------------------------------
������
--------------------------------------------------------------------*/
void PlayScene::Initialize(void)
{
	mShootingHandle = LoadGraph("Resources/Textures/allgame1.png");

	// �ϐ��Ȃǂ̃��Z�b�g
	Reset();
}

/*----------------------------------------------------------
���̃��Z�b�g
------------------------------------------------------------*/
void PlayScene::Reset(void)
{
	// ��Ԃ̏�����
	mState = PLAY_STATE_INITIALIZE;

	// �v���C���[�̏�����
	mPlayer.Initialize(mShootingHandle, &mBulletManage);

	// �e�̊Ǘ��҂̏�����
	mBulletManage.Initialize(mShootingHandle);

	// �G�̊Ǘ��҂̏�����
	mEnemyManager.Initialize(mShootingHandle, &mBulletManage);

	// �w�i�̏�����
	mBackGround.Initialize();

	mUserInterface.Initialize();

}

/*-----------------------------------------------------------
�X�V
-------------------------------------------------------------*/
int PlayScene::Update(void)
{
	int nextScene = GAME_SCENE_NONE;

	switch (mState)
	{
		// ������      =================================
		case PLAY_STATE_INITIALIZE:
		{
			
			// �ϐ��Ȃǂ̃��Z�b�g
			Reset();

			// �Q�[���f�[�^�̏�����
			g_gameData.Initialize();

			// �t�F�[�h�C����Ԃ�
			mState = PLAY_STATE_FADEIN;

			break;
		}
			// �t�F�[�h�C���@�@�@========================
		case PLAY_STATE_FADEIN:
		{
			// �t�F�[�h�̍X�V
			int res = FadeInUpdate(FADE_TIME);

			// �t�F�[�h���I�������玟�̏�Ԃ�
			if (res == FALSE)
			{
				mState = PLAY_STATE_MAIN;
			}

			break;
		}
		// ���C������	    ========================
		case PLAY_STATE_MAIN:
		{
			// �v���C���[�̍X�V
			mPlayer.Update();

			// �e�̊Ǘ��҂̍X�V
			mBulletManage.Update();

			// �G�̊Ǘ��҂̍X�V
			mEnemyManager.Update();

			// �G�ƒe�Ƃ̓����蔻��
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				// ���g�p��ԂȂ珈�����Ȃ�
				if (mEnemyManager.mEnemies[i].mIsActive == FALSE)
				{
					continue;
				}

				mBulletManage.CheckHitEnemy(&mEnemyManager.mEnemies[i]);
			}
			// �v���C���[�ƒe�̓����蔻��
			mBulletManage.CheckHitPlayer(&mPlayer);

			// �G�ƃv���C���[�Ƃ̓����蔻��
			mEnemyManager.CheckHitPlayer(&mPlayer);

			// �G�����Ȃ��Ȃ�����Q�[���I��
			if (mEnemyManager.IsEnd() == TRUE)
			{
				mState = PLAY_STATE_FADEOUT;
			}

			// 2��G�ɓ������ďI��
			if (g_gameData.mStock == 0)
			{
				mState = PLAY_STATE_FADEOUT;
			}

			break;
		}
		// �t�F�[�h�A�E�g�@�@====================
		case PLAY_STATE_FADEOUT:
		{
			// �t�F�[�h�̍X�V
			int res = FadeOutUpdate(FADE_TIME);

			// �t�F�[�h���I�������玟�̏�Ԃ�
			if (res == FALSE)
			{
				mState = PLAY_STATE_FINALIZE;
			}

			break;
		}
		// �I�������@�@=========================
		case PLAY_STATE_FINALIZE:
		{
			// ���̃V�[����
			nextScene = GAME_SCENE_RESULT;

			// �ϐ��Ȃǂ̃��Z�b�g
			Reset();

			break;
		}
	}

	return nextScene;
}

/*-------------------------------------------------
�`��
-------------------------------------------------*/
void PlayScene::Draw(void)
{
	// �w�i�̕`��
	mBackGround.Draw();
	
	// �v���C���[�̕`��
	mPlayer.Draw();

	// �e�̊Ǘ��҂̕`��
	mBulletManage.Draw();

	// �G�̊Ǘ��҂̕`��
	mEnemyManager.Draw();

	//���[�U�[�C���^�[�t�F�[�X�̕`��
	mUserInterface.Draw();
}

/*---------------------------------------------------
�I������
------------------------------------------------------*/
void PlayScene::Finalize(void)
{
	DeleteGraph(mShootingHandle);

}



