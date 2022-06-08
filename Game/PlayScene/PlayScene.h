/*
�v���C�V�[��
�쐬�� : 2020/07/02
�쐬�� : ���V�x��
*/
#pragma once

#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "BackGround.h"
#include "UserInterface.h"

struct PlayScene
{
	// �ϐ� ==================================

	// ���
	int mState;

	// �摜�n���h��
	int mShootingHandle;		// �V���[�e�B���O�n���h��

	// �v���C���[
	Player mPlayer;

	// �e�̊Ǘ���
	BulletManager mBulletManage;

	// �G�̊Ǘ���
	EnemyManager mEnemyManager;

	// �w�i
	BackGround mBackGround;

	UserInterface mUserInterface;
	
	// �֐� ==================================

	// ������
	void Initialize();

	// ��񃊃Z�b�g
	void Reset();

	// �X�V
	int Update();

	// �`��
	void Draw();

	// �I������
	void Finalize();

};
