#ifndef ENEMYMESHSHOT001_H_
#define ENEMYMESHSHOT001_H_

/**
 * 3D�G�e001 .
 * 1)�����悭�ݒ�����ɔ�яo��<BR>
 * 2)���X�ɐ����͒x���Ȃ�A���@�̕����ɕ����]��<BR>
 * 3)���̌㎞�@���߂����Ē����ړ��B�������Ă���<BR>
 * �y�㏑���\�ȃ����o�[�z
 *
 */
class EnemyMeshShot001 : public DefaultMeshEnemyActor {

	/** �o�����̏��� */
	int _iMoveVelocity_Begin;
	/** �o�����̉����x */
	int _iMoveAcceleration_Begin;
	/** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
	DWORD _dwFrame_TurnBegin;
	/** ���g���o�����Ă���A���@�̕����ɕ����]�����I������t���[�� */
	DWORD _dwFrame_TurnFinish;
	/** ���@�̕����ɕ����]�����I�������t���[�����ɍĐݒ肳��鑬�x(0���w�肷��ƍĐݒ�͍s��Ȃ�) */
	int _iMoveVelocity_TurnAfter;
	/** ���@�̕����ɕ����]�����I�������t���[�����ɍĐݒ肳�������x(0���w�肷��ƍĐݒ�͍s��Ȃ�) */
	int _iMoveAcceleration_TurnAfter;

	//angle

public:
	EnemyMeshShot001(string prm_name, string prm_model);

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	bool isOffScreen();

	/**
	 * ��OverRide �ł���
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

	virtual ~EnemyMeshShot001();
};


#endif /*ENEMYMESHSHOT001_H_*/

