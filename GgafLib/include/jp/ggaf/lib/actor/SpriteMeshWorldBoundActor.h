#ifndef GGAF_LIB_SPRITEMESHWORLDBOUNDACTOR_H_
#define GGAF_LIB_SPRITEMESHWORLDBOUNDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/ex/SpriteMeshActor.h"

namespace GgafLib {

/**
 * ê¢äEã´äE.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class SpriteMeshWorldBoundActor : public GgafDx::SpriteMeshActor {

public:
    SpriteMeshWorldBoundActor(const char* prm_name,
                              const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    int isOutOfView() override {
        //âÊñ äOîªíËñ≥Çµ
        return 0;
    }

    bool isOutOfSpacetime() const override {;
        //ÉQÅ[ÉÄç¿ïWîÕàÕäOîªíËñ≥Çµ
        return false;
    }
    virtual ~SpriteMeshWorldBoundActor();
};

}
#endif /*GGAF_LIB_WORLDBOUNDACTOR_H_*/
