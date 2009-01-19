#ifndef ENEMYMESHSHOT001_H_
#define ENEMYMESHSHOT001_H_
namespace MyStg2nd {

/**
 * 3D�G�e001 .
 * 1)�����悭�ݒ�����ɔ�яo��<BR>
 * 2)���X�ɐ����͒x���Ȃ�A���@�̕����ɕ����]��<BR>
 * 3)���̌㎞�@���߂����Ē����ړ��B�ĉ������Ă���<BR>
 * �y�㏑���\�ȃ����o�[�z
 *
 */
class EnemyMeshShot001 : public DefaultMeshEnemyActor {
public:
	//�{Actor�̃J�X�^���v���p�e�B --->
	/** �o�����̏��� */
	int _iMoveVelocity_1st;
	/** �o�����̉����x�i���Œx���Ȃ� */
	int _iMoveAcceleration_1st;
	/** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
	DWORD _dwFrame_TurnBegin;
	/** �ړ����x��� */
	int _iMoveVelocity_Top;
	/** �Œ�ۏ؈ړ����x */
	int _iMoveVelocity_Bottom;
	/** �����]���ɔ�₷���Ƃ��ł���t���[���� */
	DWORD _dwFrameInterval_Turn;
	/** �����]�����̊p���x�A���O���l */
	GgafDx9Core::angle _angVelocity_Turn;
	/** �����]�����J�n�i_dwFrame_TurnBegin�j����Đݒ肳�������x */
	int _iMoveAcceleration_2nd;
	/** �o�����Ă���̃t���[���� */
	DWORD _dwFrame_switchedToPlay;
	//<--- �{Actor�̃J�X�^���v���p�e�B

public:
	EnemyMeshShot001(string prm_name, string prm_model);

	/**
	 * ��OverRide �ł���
	 */
	virtual void initialize();

	/**
	 * ��OverRide �ł���
	 */
	virtual void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	virtual void processJudgement();

 	/**
	 * ��OverRide �ł���
	 */
	virtual bool isOffScreen();

	/**
	 * ��OverRide �ł���
	 */
	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	virtual ~EnemyMeshShot001();
};


}
#endif /*ENEMYMESHSHOT001_H_*/

