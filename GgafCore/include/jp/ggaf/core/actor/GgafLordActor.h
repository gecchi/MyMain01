#ifndef GGAFLORDACTOR_H_
#define GGAFLORDACTOR_H_

/**
 * �Ǘ��҃A�N�^�[�N���X .
 * �V�[���ƃA�N�^�[�̋��n�����s�����ʂȃA�N�^�[�ł��B<BR>
 * �S�ẴV�[��(GgafSceane�I�u�W�F�N�g)�ɕK���P�l�Ǘ��҃A�N�^�[�������o�[�ɂȂ��Ă��܂��B<BR>
 * �Ǘ��҃A�N�^�[�́A�K���A�N�^�[�c���[�̒��_�Ɉʒu���܂��B<BR>
 * �Ǘ��҃A�N�^�[(GgafLordActor)�̃T�u�A�N�^�[�͕K���w�b�h�A�N�^�[(GgafHeadActor)�ɂȂ��Ă��܂��B<BR>
 * �w�b�h�A�N�^�[(GgafHeadActor)�̉�������킹�ĎQ�Ƃ��ĉ������B
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafLordActor : public GgafActor {
public:
	GgafLordActor(GgafScene* prm_pScene_Platform) ;


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
	void processJudgement() {};

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
	 * ��OverRide �ł���<BR>
	 */
	void remove();

	/**
	 * �P��GgafActor�A������GgafDummyActor���P�Ɛe�ƂȂ�GgafActor�A���̂�<BR>
     * ��ʂƋ��ɓo�^����B
	 * ��ʂƂ́A�����Ő�������� GgafHeadActor�� �ɂȂ�B<BR>
	 * GgafHeadActor �͏����ʓo�^���������������B�Q��ڈȍ~�̓����ʓo�^�́A<BR>
	 * ������ GgafHeadActor ���g�p�����B<BR>
	 * �{�֐��͓����I�ɂ� prm_pActor �� GgafHeadActor �̎q�A�N�^�[�Ƃ��Ă��邾���ł���B<BR>
     * @param   prm_kind    ��ʖ��i��GgafHeadActor���j
     * @param   prm_pMainActor   �o�^����A�N�^�[
	 */
    void accept(actorkind prm_kind, GgafMainActor* prm_pActor);





	bool hasSubHeadActor(actorkind prm_kind);
	GgafHeadActor* getSubHeadActor(actorkind prm_kind);




	/**
	 * ������GgafHeadActor���擾����B<BR>
     * @param   prm_kind    ���("*"�ɂ��ȗ��\)
     * @param   prm_pActor   �o�^����A�N�^�[
	 */
//    virtual GgafHeadActor* getHeadActor(string prm_kind);


    /**
	 * �_�l�ɐڌ� .
	 * @return	�Ă΂�ďo�Ă����_�l
	 */
	virtual GgafGod* askGod();

	virtual ~GgafLordActor();
};
#endif /**GGAFLORDACTOR_H_*/
