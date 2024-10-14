#ifndef MYVREATH_H_
#define MYVREATH_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * Vreath .
 * @version 1.00
 * @since 2012/05/11
 * @author Masatoshi Tsuge
 */
class MyVreath : public GgafLib::DefaultMeshActor {

public:
    MyVreath(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~MyVreath();
};

}
#endif /*MYVREATH_H_*/

