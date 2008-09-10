#ifndef GGAFSCENE_H_
#define GGAFSCENE_H_

/**
 * �V�[���̊��N���X .
 * �{�v���O�����Ō����w�V�[���i��ʁj�x�Ƃ́A��ɃA�N�^�[�Ɏw������I�u�W�F�N�g��<BR>
 * �e�V�[���́A�K���P�̃A�N�^�[�c���[�������o�Ƃ��ĕێ����Ă��܂��B<BR>
 * �S�ẴV�[���N���X�́A�{�N���X�𒼐ځE�Ԑڌp�����Ȃ���΂Ȃ�܂���B<BR>
 * �܂��A�V�[�����m�ŁA�c���[�K�w�\�����̂鎖���ł��܂��B<BR>
 * �V�[���Ɏ�������Ă��郁�\�b�h�S�̂قƂ�ǂ́A�������g�Ǝ����z���̃V�[���i���c���[�V�[���j�S�Ăɉe������d�l�ɂȂ��Ă��܂��B<BR>
 * �Q�[�����I�u�W�F�N�g�w���ŕ\�����邽�߁A�l�X�ȁw�V�[���i��ʁj�x�Łw�A�N�^�[(�L����)�x���������􂷂�A�Ƃ�������O���ɂ����Đ݌v���Ă���܂��B<BR>
 * <B>�y�p��⑫�z</B>
 * <TABLE>
 * <TR>
 * <TD>�u�V�[���v</TD>
 * <TD>�V�[���N���X�̃C���X�^���X�i�I�u�W�F�N�g�j���ȗ����āA�P�ɃV�[���ƌĂԂ��Ƃɂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>���\�b�h�����s�����V�[���I�u�W�F�N�g���g���w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�T�u�V�[���v�u�T�u�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA�V�[����<B>����</B>�Ԃ牺����P�K�w���̃V�[���B���w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�V�[���z���v�u�z���v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA�V�[��<B>��</B>�Ԃ牺����S�ẴV�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�e�V�[���v�u�e�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA�V�[��<B>��</B>���ڈ����͊ԐړI�ɂԂ牺�����Ă���V�[���S�Ă��w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>���V�[���ȊO�̃V�[���S�Ă��w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�c���[�v</TD>
 * <TD>�V�[�����m���c���[�K�w�\���ɂ���ĘA������Ă���1�̂܂Ƃ܂���w���܂��B</TD>
 * </TR><TR>
 * <TD>�u�������c���[�v</TD>
 * <TD>���V�[�����܂܂�Ă���c���[�\�������S�Ďw���܂��B<</TD>
 * </TR><TR>
 * <TD>�u���c���[�v</TD>
 * <TD>���V�[���𒸓_�Ƃ���A���V�[���{���V�[���z���̃c���[�\���������w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�V�[���v</TD>
 * <TD>���V�[���{���V�[���z���̃V�[���S�Ă��w���܂��B���V�[�������c���[�̒��_�i�ł��e�j�Ɉʒu���Ă��邱�Ƃ��Ӗ����Ă��܂�</TD>
 * </TR><TR>
 * <TD>�u�V�[���N���X�v</TD>
 * <TD>GgafActor�N���X�𒼐ځE�Ԑڌp�����Ă���N���X�S�ʂ��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u��ʁv�u���ʁv</TD>
 * <TD>�V�[���N���X�̃N���X�p���֌W��\���Ă��܂��B
 * �N���X�p���֌W�̕\���́u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�ƌ��킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B</TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafScene : public GgafFactor<GgafScene> {

    friend class GgafGod;
    friend class GgafWorld;
    friend class GgafActor;
    friend class GgafHeadActor;
    friend class GgafLordActor;

protected:

	/** ���̃V�[���̊Ǘ��A�N�^�[ */
	GgafLordActor* _pLordActor;

	static GgafHeadActor* _s_apHeadActor01[];
	static GgafHeadActor* _s_apHeadActor02[];
public:
	/**
	 * �R���X�g���N�^ .
	 * �����F prm_name �V�[����<BR>
	 */
	GgafScene(string prm_name);

    /**
	 * �f�X�g���N�^ .
	 * ���V�[���̊Ǘ��A�N�^�[�̃c���[�A�N�^�[�̉�����s���Ă���B<BR>
	 * ���c���[�V�[���̉�����s���܂�<BR>
	 */
	virtual ~GgafScene();

    /**
	 * ���c���[�V�[���̎��̃t���[���ֈڂ鏈�� .
	 * ��OverRide �ł���<BR>
	 */
	virtual void nextFrame();

	/**
	 * ���c���[�V�[���̃t���[�����̐U�镑������ .
	 * ��OverRide �ł���<BR>
	 */
	virtual void behave();

    /**
	 * ���c���[�V�[���̃t���[�����̔��f���� .
	 * ��OverRide �ł���<BR>
	 */
	virtual void judge();

    /**
	 * ���c���[�V�[���̃t���[�����̕`�掖�O���� .
	 * ��OverRide �ł���<BR>
	 */
	virtual void drawPrior();

    /**
	 * ���c���[�V�[���̃t���[�����̕`�揈�� .
	 * ��OverRide �ł���<BR>
	 */
	virtual void drawMain();

    /**
	 * ���c���[�V�[���̃t���[�����̕`�掖�㏈�� .
	 * ��OverRide �ł���<BR>
	 */
	virtual void drawTerminate();

    /**
	 * ���c���[�V�[���ɉ������� .
	 * ��OverRide �ł���<BR>
	 */
	virtual void happen(int prm_no);

    /**
	 * ���c���[�V�[���ɉ������� .
	 * ��OverRide �ł���<BR>
	 */
	virtual void finally();

	/**
     * ���c���[�V�[�����Đ�����B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void declarePlay();

	virtual void playImmediately();

    /**
     * ���c���[�V�[�����~����B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void declareStop();

	virtual void stopImmediately();

    /**
     * ���c���[�V�[�����ꎞ��~����B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void declarePause();

	virtual void pauseImmediately();

    /**
     * ���c���[�V�[���̈ꎞ��~�������B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void declareUnpause();

	virtual void unpauseImmediately();

    /**
	 * ���c���[�V�[�����\������B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void declareBlind();

	virtual void blindImmediately();

    /**
	 * ���c���[�V�[���̔�\���������B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void declareUnblind();

	virtual void unblindImmediately();

    /**
	 * ���c���[�V�[����▽������B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void declareFinishLife();

    /**
	 * ���c���[�V�[����▽������B .
	 * ��OverRide �ł���<BR>
	 */
	virtual void cleane();




    /**
	 * �_�l�ɐڌ� .
	 * @return	�Ă΂�ďo�Ă����_�l
	 */
	virtual GgafGod* askGod();

	/**
	 * ���V�[���̊Ǘ��҃A�N�^�[���擾 .
	 * @return	�Ǘ��҃A�N�^�[
	 */
	virtual GgafLordActor* getLordActor();

	/**
	 * ���c���[�V�[���̃A�N�^�[�ɏՓ˔�������s (�x�����B�������getName()��string��r�Ȃ̂ł��x���B���̃��\�b�h���g�������ǂ����[).
	 * ���c���[�V�[���S�Ăɑ΂��āA�e�V�[���ɏ�������Ǘ��҃A�N�^�[�̃T�u�A�N�^�[�ł��� GgafHeadActor �S�Ăɑ΂���<BR>
	 * GgafActor#executeBumpChkRoundRobin�����s����B<BR>
	 * @param	prm_actor_kind_name01	���肷��Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor��ʖ�
	 * 		    prm_actor_kind_name02	���肳���Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor��ʖ�<BR>
	 */
	//virtual void executeBumpChkHeadActors(string prm_actor_kind_name01, string prm_actor_kind_name02);


	/**
	 * ���c���[�V�[���̃A�N�^�[�ɏՓ˔�������s �i�����ق��j.
	 * ���c���[�V�[���S�Ăɑ΂��āA�e�V�[���ɏ�������Ǘ��҃A�N�^�[�̃T�u�A�N�^�[�ł��� GgafHeadActor �S�Ăɑ΂���<BR>
	 * GgafActor#executeBumpChkRoundRobin�����s����B<BR>
	 * @param	prm_actorkind01	���肷��Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor���
	 * 		    prm_actorkind01	���肳���Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor���<BR>
	 */
	virtual void executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02);

	/**
	 * �o�߃t���[������B .
	 * ���O�� delay(n) ���s���i���ʂ�true/false�Ɋւ�炸�j�̃t���[��������̌o�߃t���[�����ɒB���������肷��B<BR>
	 * ���ӁF����q�Ŏg�p�����ꍇ�͂��܂������܂���B<BR>
	 * @param	prm_dwFrame_delay	�o�߃t���[����
	 * @return	bool	true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
	 */
//	virtual bool delayed(_delay);

	/**
	 * �f�o�b�O�p�F�c���[�\����\�� .
	 */
	virtual void dump();

	/**
	 * �f�o�b�O�p�Fdump()����g�p����� .
	 */
	virtual void dump(string prm_parent);
};

#endif /**GGAFSCENE_H_*/
