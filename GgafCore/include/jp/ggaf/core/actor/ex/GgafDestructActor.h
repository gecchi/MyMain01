#ifndef GGAFCORE_GGAFDESTRUCTACTOR_H_
#define GGAFCORE_GGAFDESTRUCTACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace GgafCore {

/**
 * �_�~�[�A�N�^�[�N���X .
 * �q�A�N�^�[�������Ȃ�΁A�����I�Ɏ��E����߂����ꎞ�I�ȃA�N�^�[�ł��B<BR>
 * �c�̍s�����̂�Ƃ��ɁA�e�A�N�^�[�ɂ���Ɖ����ƕ֗���������Ȃ��ł��傤�B<BR>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafDestructActor : public GgafMainActor {

public:
    GgafDestructActor(const char* prm_name, GgafStatus* prm_pStat = nullptr);

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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
        if (getSubFirst() == nullptr) {
            sayonara(1); //1�t���[����
        }
    }

    /**
     * �����蔻��s�v�̂��ߏ��false��Ԃ� .
     * @param prm_pOtherActor
     * @return false
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDestructActor();
};

}
#endif /*GGAFCORE_GGAFDESTRUCTACTOR_H_*/
