/*
���U���g�V�[��
�쐬�� : 2020/07/06
�쐬�� : ���V�x��
*/
#pragma once

struct ResultScene
{
	// �ϐ� ======================================
	
	// ���
	int mState;

	// �T�E���h�n���h��
	int mKeySe;

	// �֐� =======================================

	// ������
	void Initialize(void);

	// ��񃊃Z�b�g
	void Reset(void);

	// �X�V
	int Update(void);

	// �`��
	void Draw(void);

	// �I������
	void Finalize(void);

};