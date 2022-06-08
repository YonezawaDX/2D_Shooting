/*
”wŒi‚Ìˆ—
ì¬“ú : 2020/07/18
ì¬Ò : •ÄàVx‰î
*/

#include "../Utility.h"

#pragma once


struct BackGround
{
	SpriteData mSprite;
	int mBackGroundHandle;

	// ‰Šú‰»
	void Initialize(void);

	// XV
	void Draw(void);

	// I—¹ˆ—
	void Finalize(void);
};