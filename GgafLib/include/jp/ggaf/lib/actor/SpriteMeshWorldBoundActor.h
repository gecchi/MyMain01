#ifndef GGAFLIB_SPRITEMESHWORLDBOUNDACTOR_H_
#define GGAFLIB_SPRITEMESHWORLDBOUNDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshActor.h"

namespace GgafLib {

/**
 * ê¢äEã´äE.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class SpriteMeshWorldBoundActor : public GgafDxCore::GgafDxSpriteMeshActor {

public:
    SpriteMeshWorldBoundActor(const char* prm_name,
                              const char* prm_model,
                              GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    int isOutOfView() override {
        //âÊñ äOîªíËñ≥Çµ
        return 0;
    }

    bool isOutOfUniverse() override {;
        //ÉQÅ[ÉÄç¿ïWîÕàÕäOîªíËñ≥Çµ
        return false;
    }
    virtual ~SpriteMeshWorldBoundActor();
};

}
#endif /*GGAFLIB_WORLDBOUNDACTOR_H_*/
