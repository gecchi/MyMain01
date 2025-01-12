#ifndef GGAF_LIB_WORLDBOUNDACTOR_H_
#define GGAF_LIB_WORLDBOUNDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/ex/WorldBoundActor.h"

//#define RENDER_DEPTH_INDEX_WORLDBOUND (RENDER_DEPTH_INDEX_SP_BACK(4))

namespace GgafLib {

/**
 * ê¢äEã´äE.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundActor : public GgafDx::WorldBoundActor {

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

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual void drawHitArea() override {
    }

    virtual int isOutOfView() override {
        //âÊñ äOîªíËñ≥Çµ
        return 0;
    }

    virtual bool isOutOfSpacetime() const override {;
        //ÉQÅ[ÉÄç¿ïWîÕàÕäOîªíËñ≥Çµ
        return false;
    }
    virtual ~WorldBoundActor();
};

}
#endif /*GGAF_LIB_WORLDBOUNDACTOR_H_*/
