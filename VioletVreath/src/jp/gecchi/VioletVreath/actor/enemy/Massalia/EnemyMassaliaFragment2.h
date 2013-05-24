#ifndef ENEMYMASSALIAFRAGMENT2_H_
#define ENEMYMASSALIAFRAGMENT2_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaBase.h"

namespace VioletVreath {

/**
 * É}ÉbÉTÉäÉAífï–ÇÃífï–  .
 * Ë¶êŒÇÃífï–ÇÃífï–
 * @version 1.00
 * @since 2012/01/16
 * @author Masatoshi Tsuge
 */
class EnemyMassaliaFragment2 : public EnemyMassaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyMassaliaFragment2(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyMassaliaFragment2();
};

}
#endif /*ENEMYMASSALIAFRAGMENT2_H_*/

