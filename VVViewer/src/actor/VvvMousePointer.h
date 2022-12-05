#ifndef VVVMOUSEPOINTER_H_
#define VVVMOUSEPOINTER_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/MousePointerActor.h"

namespace VVViewer {

class VvvMousePointer : public GgafLib::MousePointerActor {

public:

    GgafLib::DefaultMeshActor* pI_;

    VvvMousePointer(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~VvvMousePointer();
};

}
#endif /*VVVMOUSEPOINTER_H_*/

