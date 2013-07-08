#ifndef ENEMYASSALIAFRAGMENT3_H_
#define ENEMYASSALIAFRAGMENT3_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Assalia/EnemyAssaliaBase.h"

namespace VioletVreath {

/**
 * É}ÉbÉTÉäÉAífï–ÇÃífï–  .
 * Ë¶êŒÇÃífï–ÇÃífï–
 * @version 1.00
 * @since 2012/01/17
 * @author Masatoshi Tsuge
 */
class EnemyAssaliaFragment3 : public EnemyAssaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyAssaliaFragment3(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyAssaliaFragment3();
};

}
#endif /*ENEMYASSALIAFRAGMENT3_H_*/

