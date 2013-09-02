#ifndef GGAFLIB_DEFAULTGEOMETRICACTOR_H_
#define GGAFLIB_DEFAULTGEOMETRICACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafLib {

/**
 * 表示不要のダミー用
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class DefaultGeometricActor : public GgafDxCore::GgafDxGeometricActor {

public:
    DefaultGeometricActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = nullptr, GgafDxCore::GgafDxChecker* prm_pChecker = nullptr);

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    virtual ~DefaultGeometricActor();

};

}
#endif /*GGAFLIB_DEFAULTGEOMETRICACTOR_H_*/
