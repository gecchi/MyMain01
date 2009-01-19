#ifndef GGAFWORLD_H_
#define GGAFWORLD_H_
namespace GgafCore {


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

	GgafWorld(string prm_name);

	/**
	 * ��������<BR>
	 */
	void initialize() {};

	/**
	 * �t���[�����̐U�镑��<BR>
	 */
	virtual void processBehavior() {};

	/**
	 * �t���[�����̔��菈��<BR>
	 */
	virtual void processJudgement() {};

	/**
	 * �t���[�����̕`�掖�O����<BR>
	 */
	virtual void processDrawPrior() {};

	/**
	 * �t���[�����̕`�揈��<BR>
	 */
	virtual void drawMain() {};

	/**
	 * �t���[�����̕`�揈��<BR>
	 */
	virtual void processDrawMain() {};

	/**
	 * �t���[�����̕`�掖�㏈��<BR>
	 */
	virtual void processDrawTerminate() {};

	/**
	 * �����̏���<BR>
	 * @param prm_no ������\�����l
	 */
	virtual void processHappen(int prm_no) {};

	/**
	 * �ŏI����<BR>
	 */
	virtual void processFinal() {};


	virtual ~GgafWorld();
};


}
#endif /*GGAFWORLD_H_*/
