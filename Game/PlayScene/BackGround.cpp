/*
�w�i�̏���
�쐬�� : 2020/07/18
�쐬�� : ���V�x��
*/

#include "BackGround.h"

void BackGround::Initialize(void)
{
	mBackGroundHandle = LoadGraph("Resources/Textures/WMV.gif");

	PlayMovieToGraph(mBackGroundHandle);

	mSprite.SetTexture(mBackGroundHandle);
	mSprite.pos.x = 320;
	mSprite.pos.y = 240;
	mSprite.scale.x = 3.0f;
	mSprite.scale.y = 3.0f;
}


void BackGround::Draw(void)
{
	mSprite.Draw();
}

void BackGround::Finalize(void)
{
	DeleteGraph(mBackGroundHandle);
}

