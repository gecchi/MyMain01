#ifndef GGAF_CORE_DESTRUCTACTOR_H_
#define GGAF_CORE_DESTRUCTACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace GgafCore {

/**
 * �_�~�[�A�N�^�[�N���X .
 * �q�A�N�^�[�������Ȃ�΁A�����I�Ɏ��E����߂����ꎞ�I�ȃA�N�^�[�ł��B<BR>
 * �c�̍s�����̂�Ƃ��ɁA�e�A�N�^�[�ɂ���Ɖ����ƕ֗���������Ȃ��ł��傤�B<BR>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class DestructActor : public MainActor {

public:
    DestructActor(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void processFinal() override {
        if (getChildFirst() == nullptr) {
            sayonara(1); //1�t���[����
        }
    }

    /**
     * �����蔻��s�v�̂��ߏ��false��Ԃ� .
     * @param prm_pOtherActor
     * @return false
     */
    virtual bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const Actor* prm_pOtherActor) override {
    }

    virtual ~DestructActor();
};

}
#endif /*GGAF_CORE_DESTRUCTACTOR_H_*/
