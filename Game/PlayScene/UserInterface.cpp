/*
�w�i�̏���
�쐬�� : 2020/07/22
�쐬�� : ���V�x��
*/

#include "UserInterface.h"
#include "../GameData.h"

// �萔
#define PLAYER_RECT_X1			0
#define PLAYER_RECT_Y1			0
#define PLAYER_RECT_X2			32
#define PLAYER_RECT_Y2			32

// �C���^�[�t�F�[�X�̒萔---------------------
// �X�R�A
#define UI_SCORE_X				30
#define UI_SCORE_Y				10

// �c�@
#define UI_RE_X					300
#define UI_RE_Y					10

// �t�H���g�̃T�C�Y
#define FONT_SIZE_B				32
#define FONT_SIZE_S				15


void UserInterface::Initialize(void)
{
	mPlayerStock = LoadGraph("Resources/Textures/allgame1.png");
	// �摜�̐ݒ�
	mSprite.SetTexture(mPlayerStock);
	mSprite.src.x = PLAYER_RECT_X1;
	mSprite.src.y = PLAYER_RECT_Y1;
	mSprite.size.x = PLAYER_RECT_X2;
	mSprite.size.y = PLAYER_RECT_Y2;

	mSprite.scale.x = 1.0f;
	mSprite.scale.y = 1.0f;

	mSprite.pos.x = 15;
	mSprite.pos.y = 15;

	mSprite.alpha = 1.0f;
}

void UserInterface::Draw(void)
{
	mSprite.Draw();


	// �c�@�̕\��
	DrawFormatString(
		UI_SCORE_X,
		UI_SCORE_Y,
		GetColor(255, 255, 0),
		"�~%d",
		g_gameData.mStock
	);

	// �X�R�A�̕\��
	SetFontSize(FONT_SIZE_B);
	DrawFormatString(
		UI_RE_X,
		UI_RE_Y,
		GetColor(255, 255, 0),
		"%d",
		g_gameData.mBreakScore
	);

	SetFontSize(FONT_SIZE_S);
}
