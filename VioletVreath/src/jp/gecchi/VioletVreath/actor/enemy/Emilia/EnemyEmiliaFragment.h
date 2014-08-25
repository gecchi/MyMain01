#ifndef ENEMYASSALIAFRAGMENT_H_
#define ENEMYASSALIAFRAGMENT_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmiliaBase.h"

namespace VioletVreath {

/**
 * ÉGÉ~ÉäÉAífï–  .
 * Ë¶êŒÇÃífï–
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class EnemyEmiliaFragment : public EnemyEmiliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyEmiliaFragment(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyEmiliaFragment();
};

}
#endif /*ENEMYASSALIAFRAGMENT_H_*/

