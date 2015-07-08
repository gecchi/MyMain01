#ifndef GGAFLIB_SPRITEMESHWORLDBOUNDACTOR_H_
#define GGAFLIB_SPRITEMESHWORLDBOUNDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshActor.h"

#define RENDER_DEPTH_LEVEL_WORLDBOUND (RENDER_DEPTH_LEVEL_SP_BACK1)

namespace GgafLib {

/**
 * ���E���E.
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

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    int isOutOfView() override {
        //��ʊO���薳��
        return 0;
    }

    bool isOutOfSpacetime() const override {;
        //�Q�[�����W�͈͊O���薳��
        return false;
    }
    virtual ~SpriteMeshWorldBoundActor();
};

}
#endif /*GGAFLIB_WORLDBOUNDACTOR_H_*/
