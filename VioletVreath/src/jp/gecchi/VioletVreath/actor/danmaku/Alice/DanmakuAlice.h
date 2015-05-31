#ifndef DANMAKUALICE_H_
#define DANMAKUALICE_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * ’e–‹ƒAƒŠƒXŠî’ê .
 * @version 1.00
 * @since 2015/05/27
 * @author Masatoshi Tsuge
 */
class DanmakuAlice : public GgafLib::DefaultGeometricActor {

    enum {
        PROG_INIT,
        PROG_1,
        PROG_BANPEI,
    };

    GgafCore::GgafActorDepository* pShotDepo_;

public:
    DanmakuAlice(const char* prm_name, const char* prm_shot_model_id);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {}

    virtual ~DanmakuAlice();

};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

