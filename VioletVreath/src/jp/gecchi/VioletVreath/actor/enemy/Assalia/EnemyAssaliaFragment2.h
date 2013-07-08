#ifndef ENEMYASSALIAFRAGMENT2_H_
#define ENEMYASSALIAFRAGMENT2_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Assalia/EnemyAssaliaBase.h"

namespace VioletVreath {

/**
 * É}ÉbÉTÉäÉAífï–ÇÃífï–  .
 * Ë¶êŒÇÃífï–ÇÃífï–
 * @version 1.00
 * @since 2012/01/16
 * @author Masatoshi Tsuge
 */
class EnemyAssaliaFragment2 : public EnemyAssaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyAssaliaFragment2(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyAssaliaFragment2();
};

}
#endif /*ENEMYASSALIAFRAGMENT2_H_*/

