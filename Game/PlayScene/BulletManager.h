/* 
’e‚ÌŠÇ—
ì¬“ú : 2020/06/28 
ì¬Ò : •ÄàVx‰î
*/
#pragma once

#include "Bullet.h"

#include "Collision.h"

// ‘O•ûéŒ¾
struct Enemy;
struct Player;

// ’e‚Ì”
#define BULLET_NUM		512

struct BulletManager
{
	// •Ï” ================================

	// ’e‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	int mTextureHandle;

	// ’e
	Bullet mBullets[BULLET_NUM];

	// ’e‚Ì”­Ë‰¹
	int mBulletSe;


	// ŠÖ” =================================

	// ‰Šú‰»
	void Initialize(int textureHandle);

	// XV
	void Update(void);

	// •`‰æ
	void Draw(void);

	// ’e‚Ì”­Ë
	BOOL Shot(int bulletType, int shooterType, Float2 pos);

	// ’e‚Æ“G‚Ì“–‚½‚è”»’è
	void CheckHitEnemy(Enemy* pEnemy);

	// “G‚ÆƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
	void CheckHitPlayer(Player* pPlayer);
};