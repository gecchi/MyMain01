#ifndef DANMAKUALICE_H_
#define DANMAKUALICE_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * �e���A���X��� .
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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {}

    virtual ~DanmakuAlice();

};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

