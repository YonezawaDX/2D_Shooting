/*
�w�i�̏���
�쐬�� : 2020/07/18
�쐬�� : ���V�x��
*/

#include "../Utility.h"

#pragma once


struct BackGround
{
	SpriteData mSprite;
	int mBackGroundHandle;

	// ������
	void Initialize(void);

	// �X�V
	void Draw(void);

	// �I������
	void Finalize(void);
};