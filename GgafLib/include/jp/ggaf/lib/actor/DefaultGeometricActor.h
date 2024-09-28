#ifndef GGAF_LIB_DEFAULTGEOMETRICACTOR_H_
#define GGAF_LIB_DEFAULTGEOMETRICACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
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
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pWorldCollisionChecker;
public:
    DefaultGeometricActor(const char* prm_name);

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    //virtual GgafDx::CollisionChecker* createChecker() override;

    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }
    virtual void drawHitArea() override;

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {}

    virtual ~DefaultGeometricActor();

};

}
#endif /*GGAF_LIB_DEFAULTGEOMETRICACTOR_H_*/
