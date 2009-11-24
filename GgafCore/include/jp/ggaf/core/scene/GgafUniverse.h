#ifndef GGAFUNIVERSE_H_
#define GGAFUNIVERSE_H_
namespace GgafCore {

/**
 * ���̐��N���X .
 * �{�v���O�����Ō����w���̐��x�Ƃ́A�S�ẴV�[��(GgafScene�I�u�W�F�N�g)�̒��_�Ɉʒu������ʂȃV�[���ł��B<BR>
 * �_���炪 new ���Ă���܂��B�{�N���X�� new �����ƁA���Â�I�ɃV�[��(GgafScene)�� new ����܂��B<BR>
 * ���Ȃ��Ƃ��P�͂��̐���new���Ȃ���΂����܂���B<BR>
 * @version 1.00
 * @since 2007/11/20
 * @author Masatoshi Tsuge
 */
class GgafUniverse : public GgafMainScene {
    friend class GgafGod;
    friend class GgafScene;

public:

    GgafUniverse(const char* prm_name);

    /**
     * ��������<BR>
     */
    void initialize() {
    }

    /**
     * �t���[�����̐U�镑��<BR>
     */
    virtual void processBehavior() {
    }

    /**
     * �t���[�����̔��菈��<BR>
     */
    virtual void processJudgement() {

    }

    /**
     * �t���[�����̕`�掖�O����<BR>
     */
    virtual void processPreDraw() {
    }

    /**
     * �t���[�����̕`�揈��<BR>
     */
    virtual void draw() {
    }

    /**
     * �t���[�����̕`�揈��<BR>
     */
    virtual void processDraw() {
    }

    /**
     * �t���[�����̕`�掖�㏈��<BR>
     */
    virtual void processAfterDraw() {
    }

    /**
     * �����̏���<BR>
     * @param prm_no ������\�����l
     */
    virtual void processHappen(int prm_no) {
    }

    /**
     * �ŏI����<BR>
     */
    virtual void processFinal() {
    }

    virtual ~GgafUniverse();
};

}
#endif /*GGAFUNIVERSE_H_*/
