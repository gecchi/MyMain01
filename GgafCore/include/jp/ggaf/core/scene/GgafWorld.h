#ifndef GGAFWORLD_H_
#define GGAFWORLD_H_

#define MAX_DEPTH_LEVEL 2028
/**
 * ���E�̊��N���X .
 * �{�v���O�����Ō����w���E�x�Ƃ́A�S�ẴV�[��(GgafScene�I�u�W�F�N�g)�̒��_�Ɉʒu������ʂȃV�[���ł��B<BR>
 * ���Ȃ��Ƃ��P�͐��E��new���Ȃ���΂����܂���B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
 class GgafWorld : public GgafMainScene {
    friend class GgafGod;
    friend class GgafScene;

public:
	/** �A�N�^�[���������_�����O�̂��߂̉����̃��x���O���[�v */
    static GgafActor* _apActorDrawDepthLevel_first[];
	/** �A�N�^�[���������_�����O�̂��߂̉����̃��x���O���[�v�ʍŏI�A�N�^�[ */
    static GgafActor* _apActorDrawDepthLevel_last[];


	GgafWorld(string prm_name);

	/**
	 * ��������<BR>
	 */
	void initialize() {};

	/**
	 * �t���[�����̐U�镑��<BR>
	 */
	void processBehavior() {};

	/**
	 * �t���[�����̔��菈��<BR>
	 */
	void processJudgement() {};

	/**
	 * �t���[�����̕`�掖�O����<BR>
	 */
	void processDrawPrior() {};

	/**
	 * �t���[�����̕`�揈��<BR>
	 */
	void drawMain();

	/**
	 * �t���[�����̕`�揈��<BR>
	 */
	void processDrawMain() {};

	/**
	 * �t���[�����̕`�掖�㏈��<BR>
	 */
	void processDrawTerminate() {};

	/**
	 * �����̏���<BR>
	 * @param prm_no ������\�����l
	 */
	void processHappen(int prm_no) {};

	/**
	 * �ŏI����<BR>
	 */
	void processFinal() {};

	/**
	 * �`�惌�x���i�����j��o�^
	 * @param prm_iDrawDepthLevel ���x��
	 * @param prm_pActor �A�N�^�[
	 */
	static void setDrawDepthLevel(int prm_iDrawDepthLevel, GgafActor* prm_pActor);

	virtual ~GgafWorld();
};


#endif /*GGAFWORLD_H_*/
