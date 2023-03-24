#ifndef ENEMYASSALIAFRAGMENT2_H_
#define ENEMYASSALIAFRAGMENT2_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmiliaBase.h"

namespace VioletVreath {

/**
 * ÉGÉ~ÉäÉAífï–ÇÃífï–  .
 * Ë¶êŒÇÃífï–ÇÃífï–
 * @version 1.00
 * @since 2012/01/16
 * @author Masatoshi Tsuge
 */
class EnemyEmiliaFragment2 : public EnemyEmiliaBase {

protected:
    void processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) override;

public:
    EnemyEmiliaFragment2(const char* prm_name);

    void onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) override;

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyEmiliaFragment2();
};

}
#endif /*ENEMYASSALIAFRAGMENT2_H_*/

