#ifndef GGAFLIB_WORLDBOUNDACTOR_H_
#define GGAFLIB_WORLDBOUNDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxWorldBoundActor.h"

namespace GgafLib {

/**
 * ���E���E.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundActor : public GgafDxCore::GgafDxWorldBoundActor {

public:
    frame _offset_frames;

public:
    WorldBoundActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void processSettlementBehavior() override;

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    virtual int isOutOfView() override {
        //��ʊO���薳��
        return 0;
    }

    virtual bool isOutOfSpacetime() const override {;
        //�Q�[�����W�͈͊O���薳��
        return false;
    }
    virtual ~WorldBoundActor();
};

}
#endif /*GGAFLIB_WORLDBOUNDACTOR_H_*/
