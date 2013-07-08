#ifndef ENEMYERMIONEARMWEAK_H_
#define ENEMYERMIONEARMWEAK_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArm.h"

namespace VioletVreath {

/**
 * 敵機エミオネの触手の弱点 .
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArmWeak : public EnemyErmioneArm {

public:
    EnemyErmioneArmWeak(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyErmioneArmWeak();
};

}
#endif /*ENEMYERMIONEARMWEAK_H_*/

