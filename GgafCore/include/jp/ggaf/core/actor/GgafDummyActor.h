#ifndef GGAFDUMMYACTOR_H_
#define GGAFDUMMYACTOR_H_
namespace GgafCore {

/**
 * �_�~�[�A�N�^�[�N���X .
 * �q�A�N�^�[�������Ȃ�Ύ����I�Ɏ��E����߂����A�N�^�[�ł��B<BR>
 * �c�̍s�����̂�Ƃ��ɁA�e�A�N�^�[�ɂ���ƕ֗���������܂���B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafDummyActor : public GgafMainActor {

public:
	GgafDummyActor(std::string prm_name);

	/**
	 * ��������<BR>
	 */
	virtual void initialize() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processBehavior() {};

 	/**
 	 * �T�u��������Ύ��S���܂��B
	 * ��OverRide �ł���<BR>
	 */
	virtual void processJudgement() {
		if (getSubFirst() == NULL) {
			farewell();
		}
	}

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawPrior() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	virtual void processDrawMain() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	virtual void processDrawTerminate() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	virtual void processHappen(int prm_no) {};

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processFinal() {};

	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
 		return false;
 	};

	/**
	 * ��OverRide �ł���<BR>
	 */
 	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	virtual ~GgafDummyActor();
};


}
#endif /*GGAFDUMMYACTOR_H_*/
