#ifndef ENEMYASSALIAFRAGMENT3_H_
#define ENEMYASSALIAFRAGMENT3_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmiliaBase.h"

namespace VioletVreath {

/**
 * ÉGÉ~ÉäÉAífï–ÇÃífï–  .
 * Ë¶êŒÇÃífï–ÇÃífï–
 * @version 1.00
 * @since 2012/01/17
 * @author Masatoshi Tsuge
 */
class EnemyEmiliaFragment3 : public EnemyEmiliaBase {

protected:
    void processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) override;

public:
    EnemyEmiliaFragment3(const char* prm_name);

    void onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) override;

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyEmiliaFragment3();
};

}
#endif /*ENEMYASSALIAFRAGMENT3_H_*/

