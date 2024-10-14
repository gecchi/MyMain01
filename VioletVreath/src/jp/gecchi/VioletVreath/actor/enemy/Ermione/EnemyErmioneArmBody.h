#ifndef ENEMYERMIONEARMBODY_H_
#define ENEMYERMIONEARMBODY_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArm.h"

namespace VioletVreath {

/**
 * 敵機エルミオネの触手の胴体 .
 * グラの触手に挑戦ッッ！！！
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArmBody : public EnemyErmioneArm {
public:

    EnemyErmioneArmBody(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~EnemyErmioneArmBody();
};

}
#endif /*ENEMYERMIONEARMBODY_H_*/

