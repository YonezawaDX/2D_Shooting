/*
�G�̊Ǘ�
�쐬�� : 2020/06/30
�쐬�� : ���V�x��
*/
#pragma once

#include "Enemy.h"

#include "BulletManager.h"

// �O���錾
struct Player;

// �G�̐�
#define ENEMY_NUM		32

struct EnemyManager
{
	// �ϐ� ====================================

	// �G�̉摜�n���h��
	int mTextureHandle;

	// �G
	Enemy mEnemies[ENEMY_NUM];

	// �e�̊Ǘ��҃|�C���^�i�A����j
	BulletManager* mpBulletManager;

	// �G�����p�̃^�C�}�[
	int mTimer;

	// �G�̐����z����Q�Ɣԍ�
	int mArrivalIdx;

	// �֐� ===========================

	// ������
	void Initialize(int txtureHandle, BulletManager* pBulletManager);

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �G�ƃv���C���[�̓����蔻��
	void CheckHitPlayer(Player* pPlayer);

	// �I������
	BOOL IsEnd(void);
};