#ifndef SHOT002_H_
#define SHOT002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * ”Ä—p’e002(¬) .
 * ”j‰ó‰Â”\‚Å“™‘¬’¼üˆÚ“®ŒãA©‹@‚Ö•ûŒü“]Š·<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot002 : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    Shot002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~Shot002();
};

}
#endif /*SHOT002_H_*/

