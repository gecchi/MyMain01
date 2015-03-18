#ifndef SHOT003_H_
#define SHOT003_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * ”Ä—p’e003(¬) .
 * ”j‰ó•s‰Â”\‚Å“™‘¬’¼üˆÚ“®<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot003 : public GgafLib::DefaultMeshSetActor {

public:
    Shot003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Shot003();
};

}
#endif /*SHOT003_H_*/

