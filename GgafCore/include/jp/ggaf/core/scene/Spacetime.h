#ifndef GGAF_CORE_SPACETIME_H_
#define GGAF_CORE_SPACETIME_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/scene/MainScene.h"

#include "jp/ggaf/core/Caretaker.h"

namespace GgafCore {

/**
 * ���̐��N���X .
 * �{�v���O�����ł́w���̐��x�Ƃ́A�S�ẴV�[���K�w�\���̒��_�Ɉʒu������ʂȃV�[���ł��B
 * �Ǘ���(Caretaker)���炪 new ���Ă���܂��B�{�N���X�� new �����ƁA���Â�I�ɔz���V�[��(Scene)�� new ����܂��B
 * �A�v���P�[�V�����ŏ��Ȃ��Ƃ��P�͂��̐���new���Ȃ���΂����܂���B
 * �w���̐��x �ւ̃��\�b�h���s�́A�S�ẴV�[���ƃA�N�^�[�ɉe�����܂��B
 * @version 1.00
 * @since 2009/07/23
 * @author Masatoshi Tsuge
 */
class Spacetime : public MainScene {
    friend class Caretaker;
    friend class Scene;

public:
#ifdef MY_DEBUG
    /** processHitCheck() ���s������ true */
    bool _is_running_processHitCheck;
#endif

    Spacetime(const char* prm_name);

    /**
     * �������� .
     */
    void initialize() override {
    }

    /**
     * �t���[�����̐U�镑������ .
     */
    virtual void processBehavior() override {
    }

    /**
     * �t���[�����̐U�镑���̎��㏈�� .
     */
    virtual void processSettlementBehavior() override {
    }

    /**
     * �t���[�����̔��菈�� .
     */
    virtual void processJudgement() override {
    }

    /**
     * �t���[�����̓����蔻����s���� .
     */
    virtual void processHitCheck() = 0;

    /**
     * �t���[�����̕`�掖�O���� .
     */
    virtual void processPreDraw() override {
    }

    /**
     * �t���[�����̕`�揈�� .
     */
    virtual void draw() override {
    }

    /**
     * �t���[�����̕`�揈�� .
     */
    virtual void processDraw() override {
    }

    /**
     * �t���[�����̕`�掖�㏈�� .
     */
    virtual void processAfterDraw() override {
    }

    /**
     * �����̃C�x���g���� .
     * @param prm_event_val �C�x���g�ԍ�
     * @param prm_pSource �C�x���g������
     */
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    /**
     * �ŏI���� .
     */
    virtual void processFinal() override {
    }

    void updateActiveInTheTree() override;

    virtual ~Spacetime();
};

}
#endif /*GGAF_CORE_SPACETIME_H_*/
