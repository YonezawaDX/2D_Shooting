/*
�^�C�g���V�[��
�쐬�� : 2020/06/22
�쐬�� : ���V�x��
*/
#pragma once

#include "../Utility.h"
#include "BulletManager.h"
#include "Collision.h"

struct Player
{
	// �ϐ� ====================================

	// ���
	int mState;

	// �摜�`��\����
	SpriteData mSprite;

	// ���W
	Float2 mPos;

	// �e�̊Ǘ��҂̃|�C���^ (�A����)
	BulletManager* mpBulletManager;

	// �e�̔��ˊԊu�Ǘ��p�̃^�C�}�[
	int mShootIntervalTimer;

	// �����蔻��
	CircleCollider mCollision;

	// �����p�^�C�}�[
	int mBombTimer;

	// ���G�^�C�}�[
	int mInvTimer;

	// �e�̔��ˉ�
	int mBulletSe;

	// �֐� =====================================

	// ������
	void Initialize(int textureHandle, BulletManager* pBulletManager);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// �ړ�
	void Move(void);

	// �_���[�W����
	void Damage(void);

	// ��e�����m�F
	BOOL IsDamage(void);
};