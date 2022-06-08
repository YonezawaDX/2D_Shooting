/*
�v���C���[
�쐬�� : 2020/06/04
�쐬�� : ���V�x��
*/
#pragma once

#include "../Utility.h"
#include "BulletManager.h"
#include "Collision.h"

struct Enemy
{
	// �ϐ� ============================

	// �G�̎��
	int mType;

	// ���
	int mState;

	// HP
	int mHp;

	// �摜���
	SpriteData mSprite;

	// ���W
	Float2 mPos;

	// ���x
	Float2 mVel;

	// �g�p����Ă��邩�̃t���O
	BOOL mIsActive;

	// �e�̊Ǘ��҂̃|�C���^�i�A����j
	BulletManager* mpBulletManager;

	// �����蔻����
	CircleCollider mCollision;

	// �e���˗p�̃^�C�}�[
	int mShotTimer;

	// ���j�����p�̃^�C�}�[
	int mBombTimer;

	// �G�̂��ꉹ
	int mBombSe;

	// �J�E���^�[
	int counter;

	// �֐� ==================================

	// ������
	void Initialize(int textureHandle, int enemyType, BulletManager* pBulletManager);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// �_���[�W����
	void Damage(int damage);
};