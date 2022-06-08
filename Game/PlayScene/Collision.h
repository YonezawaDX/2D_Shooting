/*
“–‚½‚è”»’è\‘¢‘Ì
ì¬“ú : 2020/07/02
ì¬Ò : •ÄàVx‰î
*/
#pragma once

#include "../Utility.h"

// ‰~‚Ì”»’è—p\‘¢‘Ì
struct CircleCollider
{
	// •Ï” ===================================

	// ”¼Œa
	float mRadius;

	// À•W
	Float2 mPos;

	// ŠÖ” ====================================

	// ‘¼‚Ì‰~‚Æ‚Ì“–‚½‚è”»’è
	BOOL CheckHit(CircleCollider collider);
};