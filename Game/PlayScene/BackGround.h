/*
wiĖ
ėŽú : 2020/07/18
ėŽŌ : ÄāVxî
*/

#include "../Utility.h"

#pragma once


struct BackGround
{
	SpriteData mSprite;
	int mBackGroundHandle;

	// úŧ
	void Initialize(void);

	// XV
	void Draw(void);

	// Iđ
	void Finalize(void);
};