#ifndef MYWAVE001_H_
#define MYWAVE001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

class MyWave001 : public GgafLib::DefaultMeshActor {

public:
    MyWave001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~MyWave001();
};

}
#endif /*MYWAVE001_H_*/

