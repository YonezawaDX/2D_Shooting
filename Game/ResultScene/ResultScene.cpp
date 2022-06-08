#include "ResultScene.h"

#include "../GameMain.h"
#include "../GameData.h"

//  �V�[���̏��
enum RESULT_STATE
{
	RESULT_STATE_INITIALIZE,		// ������

	RESULT_STATE_FADEIN,			// �t�F�[�h�C���҂��̏��
	RESULT_STATE_MAIN,				// ���C������
	RESULT_STATE_FADEOUT,			// �t�F�[�h�A�E�g���

	RESULT_STATE_FINALIZE,			// �I������

};

// ���U���g�����̍��W
#define RESULT_LOGO_POS_X			(SCREEN_CENTER_X - 100)
#define RESULT_LOGO_POS_Y			(SCREEN_CENTER_Y - 100)

// ���U���g�����̃T�C�Y
#define RESULT_LOGO_SIZE			50

// ���ʕ����̍��W
#define RESULT_POS_X				(SCREEN_CENTER_X - 100)
#define RESULT_POS_Y				(SCREEN_CENTER_Y + 100)

// ���ʕ����̃T�C�Y
#define RESULT_SIZE					30

// �c�@�̕����̍��W
#define RE_POS_Y					(RESULT_LOGO_POS_Y + 70)

/*------------------------------------------------
������
-------------------------------------------------*/
void ResultScene::Initialize(void)
{
	mKeySe = LoadSoundMem("Resources/Audio/SE00.ogg");
	
	// �ϐ��Ȃǂ̃��Z�b�g
	Reset();
}

/*------------------------------------------------
���̃��Z�b�g
----------------------------------------------------*/
void ResultScene::Reset(void)
{
	// ��Ԃ̏�����
	mState = RESULT_STATE_INITIALIZE;
}

/*-----------------------------------------------------
�X�V
------------------------------------------------------*/
int ResultScene::Update(void)
{
	int nextScene = GAME_SCENE_NONE;

	switch (mState)
	{
		// ������       ==================================
		case RESULT_STATE_INITIALIZE:
		{
			// �ϐ��Ȃǂ̃��Z�b�g
			Reset();

			// �t�F�[�h�C����Ԃ�
			mState = RESULT_STATE_FADEIN;

			// �t�F�[�h�A�E�g�ς݂̏�Ԃɂ���
			SetFadeOut();

			break;
		}
		// �t�F�[�h�C��		===============================
		case  RESULT_STATE_FADEIN:
		{
			// �t�F�[�h�̍X�V
			int res = FadeInUpdate(FADE_TIME);

			// �t�F�[�h���I�������玟�̏�Ԃ�
			if (res == FALSE)
			{
				mState = RESULT_STATE_MAIN;
			}

			break;
		}
		// ���C������		================================
		case RESULT_STATE_MAIN:
		{
			// �{�^�������������玟��
			if (IsButtonPressed(PAD_INPUT_1) == TRUE)
			{
				// ���艹
				PlaySoundMem(mKeySe, DX_PLAYTYPE_BACK);

				mState = RESULT_STATE_FADEOUT;
			}

			break;
		}
		// �t�F�[�h�A�E�g		===================================
		case RESULT_STATE_FADEOUT:
		{
			// �t�F�[�h�̍X�V
			int res = FadeOutUpdate(FADE_TIME);

			// �t�F�[�h���I�������玟�̏�Ԃ�
			if (res == FALSE)
			{
				mState = RESULT_STATE_FINALIZE;
			}

			break;
		}
		// �I������			===========================
		case RESULT_STATE_FINALIZE:
		{
			// ���̃V�[����
			nextScene = GAME_SCENE_TITLE;

			// �ϐ��Ȃǂ̃��Z�b�g
			Reset();

			break;
		}
	}

	return nextScene;
}

/*-------------------------------------------------
�`��
--------------------------------------------------*/
void ResultScene::Draw(void)
{
	int defaultSize = GetFontSize();

	// ���U���g�����̕\��

	SetFontSize(RESULT_LOGO_SIZE);

	DrawFormatString(
		RESULT_LOGO_POS_X,
		RESULT_LOGO_POS_Y,
		GetColor(255, 255, 0),
		"���U���g"
	);

	// �X�R�A�̕\��
	SetFontSize(RESULT_SIZE);

	DrawFormatString(
		RESULT_POS_X,
		RESULT_POS_Y,
		GetColor(255, 255, 0),
		"�X�R�A : %d",
		g_gameData.mBreakScore
	);

	// �c�@�̕\��
	DrawFormatString(
		RESULT_POS_X,
		RE_POS_Y,
		GetColor(255, 255, 0),
		" �c�@ : %d",
		g_gameData.mStock
	);



	SetFontSize(defaultSize);
}

/*-------------------------------------------------------------
�I������
--------------------------------------------------*/
void ResultScene::Finalize(void)
{
}
