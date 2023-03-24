#ifndef ENEMYASSALIA_H_
#define ENEMYASSALIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmiliaBase.h"

namespace VioletVreath {

/**
 * ÉGÉ~ÉäÉA  .
 * Ë¶êŒåQÇÃË¶êŒ
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyEmilia : public EnemyEmiliaBase {

protected:
    void processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) override;

public:
    EnemyEmilia(const char* prm_name);

    void onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) override;

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyEmilia();
};

}
#endif /*ENEMYASSALIA_H_*/

