#ifndef GGAF_CORE_SPACETIME_H_
#define GGAF_CORE_SPACETIME_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/scene/MainScene.h"

#include "jp/ggaf/core/Caretaker.h"

namespace GgafCore {

/**
 * ���̐��N���X .
 * �{�v���O�����ł́w���̐��x�Ƃ́A�S�ẴV�[���K�w�\���̒��_�Ɉʒu������ʂȃV�[���ł��B<BR>
 * �Ǘ���(Caretaker)���炪 new ���Ă���܂��B�{�N���X�� new �����ƁA���Â�I�ɔz���V�[��(Scene)�� new ����܂��B<BR>
 * �A�v���P�[�V�����ŏ��Ȃ��Ƃ��P�͂��̐���new���Ȃ���΂����܂���B<BR>
 * �w���̐��x �ւ̃��\�b�h���s�́A�S�ẴV�[���ƃA�N�^�[�ɉe�����܂��B<BR>
 * @version 1.00
 * @since 2009/07/23
 * @author Masatoshi Tsuge
 */
class Spacetime : public MainScene {
    friend class Caretaker;
    friend class Scene;

public:
    Spacetime(const char* prm_name);

    /**
     * ��������<BR>
     */
    void initialize() override {
    }

    /**
     * �t���[�����̐U�镑������<BR>
     */
    virtual void processBehavior() override {
    }

    /**
     * �t���[�����̐U�镑���̎��㏈��<BR>
     */
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
     * �����̃C�x���g����<BR>
     * @param prm_no �C�x���g�ԍ�
     * @param prm_pSource �C�x���g������
     */
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    /**
     * �ŏI����<BR>
     */
    virtual void processFinal() override {
    }

    void updateActiveInTheTree() override;

    virtual ~Spacetime();
};

}
#endif /*GGAF_CORE_SPACETIME_H_*/
