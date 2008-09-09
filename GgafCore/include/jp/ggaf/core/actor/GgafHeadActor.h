#ifndef GGAFHEADACTOR_H_
#define GGAFHEADACTOR_H_



/**
 * �w�b�h�A�N�^�[�N���X .
 * �L�����N�^��\������A�N�^�[��Z�߂ăO���[�v�ɂ��A�z���̃A�N�^�[�̎�ʂ�\���A�N�^�[�ɂȂ�܂��B<BR>
 * ��ʂƂ́A�����蔻�莩�� [���@�̒e]��[�G�{��] ���� [] �̒��g��\�����̂ł��B<BR>
 * �w�b�h�A�N�^�[�͔z���̃A�N�^�[�����ł���ƁA���̃t���[���Ɏ��g�����E���܂��B<BR>
 * �Ǘ��҃A�N�^�[(GgafLordActor)�̃T�u�A�N�^�[�́A�S�ĕK�����̃w�b�h�A�N�^�[�ɂȂ��Ă��܂��B<BR>
 * �܂��A�w�b�h�A�N�^�[�z���Ƀw�b�h�A�N�^�[�����݂��Ă͂����Ȃ����ƂɂȂ��Ă��܂��B<BR>
 * ���⑫�F�I�u�W�F�N�g�C���[�W�}��<BR>
 * <PRE>
 * �@�@�@�@����� GgafScene �� GgafScene �̥��
 * �@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�@�@�������o�[
 * �@�@�@�@�@GgafLordActor�@�i��1��Scene�ɕK���P��LordActor�j
 * �@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�@�bSubFirst
 * �@�@�@�@�@�@�@��
 * �@�@GgafHeadActor �� GgafHeadActor �� GgafHeadActor ��
 * �@�@�@�@�@�@�b�@�@�@�@�@�@�@�@�b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@�bSubFirst�@�@�@�b�@�@�@�@�@�@�@�@�@�b
 * �@�@�@�@�@�@���@�@�@�@�@�@�@�@���@�@�@�@�@�@�@�@�@��
 * �@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[�B�@�@�L�����̃A�N�^�[
 * </PRE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafHeadActor : public GgafActor {

public:

	actorkind _kind;

	GgafHeadActor(actorkind prm_kind);

	/**
	 * ��������<BR>
	 */
	void initialize() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	void processBehavior() {};

 	/**
	 * ��OverRide �ł���<BR>
	 */
	void processJudgement();

	/**
	 * ��OverRide �ł���<BR>
	 */
 	void processDrawPrior() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	void processDrawMain() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	void processDrawTerminate() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
	void processHappen(int prm_no) {};

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processFinal() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
 		return false;
 	};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent) {};

    /**
	 * �_�l�ɐڌ� .
	 * @return	�Ă΂�ďo�Ă����_�l
	 */
	virtual GgafGod* askGod();

	virtual ~GgafHeadActor();
};


#endif /*GGAFHEADACTOR_H_*/
