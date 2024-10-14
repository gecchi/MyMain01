#ifndef POINTERTEST_H_
#define POINTERTEST_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/MousePointerActor.h"

namespace Mogera {

class PointerTest : public GgafLib::MousePointerActor {

public:
    PointerTest(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~PointerTest();
};

}
#endif /*POINTERTEST_H_*/

