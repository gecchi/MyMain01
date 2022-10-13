#ifndef MOUSEPOINTER_H_
#define MOUSEPOINTER_H_
#include "VioletVreath.h"
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

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~MousePointer();
};

}
#endif /*MOUSEPOINTER_H_*/

