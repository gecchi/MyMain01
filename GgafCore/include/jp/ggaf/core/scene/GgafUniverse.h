#ifndef GGAFUNIVERSE_H_
#define GGAFUNIVERSE_H_
namespace GgafCore {

/**
 * ���̐��N���X .
 * �{�v���O�����Ō����w���̐��x�Ƃ́A�S�ẴV�[��(GgafScene�I�u�W�F�N�g)�̒��_�Ɉʒu������ʂȃV�[���ł��B<BR>
 * �_(GgafGod)���炪 new ���Ă���܂��B�{�N���X�� new �����ƁA���Â�I�ɔz���V�[��(GgafScene)�� new ����܂��B<BR>
 * �A�v���P�[�V�����ŏ��Ȃ��Ƃ��P�͂��̐���new���Ȃ���΂����܂���B<BR>
 * �w���̐��x �ւ̃��\�b�h���s�́A�S�ẴV�[���ƃA�N�^�[�ɉe�����܂��B<BR>
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
    virtual void processSettlementBehavior() override {
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
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
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
