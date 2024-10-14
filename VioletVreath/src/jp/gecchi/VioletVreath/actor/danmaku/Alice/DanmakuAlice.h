#ifndef DANMAKUALICE_H_
#define DANMAKUALICE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * ’e–‹ƒAƒŠƒXŠî’ê .
 * @version 1.00
 * @since 2015/05/27
 * @author Masatoshi Tsuge
 */
class DanmakuAlice : public GgafLib::DefaultGeometricActor {

    GgafCore::ActorDepository* pShotDepo_;

public:
    DanmakuAlice(const char* prm_name, const char* prm_shot_model);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {}

    virtual ~DanmakuAlice();

};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

