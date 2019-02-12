#ifndef GGAF_LIB_DEFAULTGEOMETRICACTOR_H_
#define GGAF_LIB_DEFAULTGEOMETRICACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafLib {

/**
 * 表示不要のダミー用
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class DefaultGeometricActor : public GgafDx::GeometricActor {

public:
    DefaultGeometricActor(const char* prm_name, GgafCore::Status* prm_pStat = nullptr, GgafDx::Checker* prm_pChecker = nullptr);

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {}

    virtual ~DefaultGeometricActor();

};

}
#endif /*GGAF_LIB_DEFAULTGEOMETRICACTOR_H_*/
