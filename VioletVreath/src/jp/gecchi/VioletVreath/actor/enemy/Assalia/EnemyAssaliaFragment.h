#ifndef ENEMYASSALIAFRAGMENT_H_
#define ENEMYASSALIAFRAGMENT_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Assalia/EnemyAssaliaBase.h"

namespace VioletVreath {

/**
 * マッサリア断片  .
 * 隕石の断片
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class EnemyAssaliaFragment : public EnemyAssaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyAssaliaFragment(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyAssaliaFragment();
};

}
#endif /*ENEMYASSALIAFRAGMENT_H_*/

