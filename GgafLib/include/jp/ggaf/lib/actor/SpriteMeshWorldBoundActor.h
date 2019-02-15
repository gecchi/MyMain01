#ifndef GGAF_LIB_SPRITEMESHWORLDBOUNDACTOR_H_
#define GGAF_LIB_SPRITEMESHWORLDBOUNDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/ex/SpriteMeshActor.h"

namespace GgafLib {

/**
 * ���E���E.
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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
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
#endif /*GGAF_LIB_WORLDBOUNDACTOR_H_*/
