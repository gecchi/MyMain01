#ifndef GGAFUNIVERSE_H_
#define GGAFUNIVERSE_H_
namespace GgafCore {

/**
 * ���̐��N���X .
 * �{�v���O�����Ō����w���̐��x�Ƃ́A�S�ẴV�[��(GgafScene�I�u�W�F�N�g)�̒��_�Ɉʒu������ʂȃV�[���ł��B<BR>
 * �_���炪 new ���Ă���܂��B�{�N���X�� new �����ƁA���Â�I�ɃV�[��(GgafScene)�� new ����܂��B<BR>
 * ���Ȃ��Ƃ��P�͂��̐���new���Ȃ���΂����܂���B<BR>
 * @version 1.00
 * @since 2009/07/23
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
    void initialize() override {
    }

    /**
     * �t���[�����̐U�镑��<BR>
     */
    virtual void processBehavior() override {
    }

    /**
     * �t���[�����̔��菈��<BR>
     */
    virtual void processJudgement() override {

    }

    /**
     * �t���[�����̕`�掖�O����<BR>
     */
    virtual void processPreDraw() override {
    }

    /**
     * �t���[�����̕`�揈��<BR>
     */
    virtual void draw() override {
    }

    /**
     * �t���[�����̕`�揈��<BR>
     */
    virtual void processDraw() override {
    }

    /**
     * �t���[�����̕`�掖�㏈��<BR>
     */
    virtual void processAfterDraw() override {
    }

    /**
     * �����̏���<BR>
     * @param prm_no ������\�����l
     */
    virtual void processHappen(int prm_no) override {
    }

    /**
     * �ŏI����<BR>
     */
    virtual void processFinal() override {
    }

    virtual ~GgafUniverse();
};

}
#endif /*GGAFUNIVERSE_H_*/
