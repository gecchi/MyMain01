#ifndef ENEMYHERMIONEARMWEAK_H_
#define ENEMYHERMIONEARMWEAK_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Hermione/EnemyHermioneArm.h"

namespace VioletVreath {

/**
 * 敵機ヘルミオネの触手の弱点 .
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArmWeak : public EnemyHermioneArm {

public:
    EnemyHermioneArmWeak(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyHermioneArmWeak();
};

}
#endif /*ENEMYHERMIONEARMWEAK_H_*/

