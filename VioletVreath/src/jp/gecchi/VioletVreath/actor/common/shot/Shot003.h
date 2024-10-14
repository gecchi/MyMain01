#ifndef SHOT003_H_
#define SHOT003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * ”Ä—p’e003(¬) .
 * ”j‰ó•s‰Â”\‚Å“™‘¬’¼üˆÚ“®<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot003 : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    Shot003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~Shot003();
};

}
#endif /*SHOT003_H_*/

