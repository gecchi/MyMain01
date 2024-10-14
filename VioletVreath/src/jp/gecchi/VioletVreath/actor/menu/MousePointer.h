#ifndef MOUSEPOINTER_H_
#define MOUSEPOINTER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/MousePointerActor.h"

namespace VioletVreath {

class MousePointer : public GgafLib::MousePointerActor {

public:
    MousePointer(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~MousePointer();
};

}
#endif /*MOUSEPOINTER_H_*/

