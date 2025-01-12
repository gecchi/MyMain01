#ifndef ENEMYERMIONEARMHEAD_H_
#define ENEMYERMIONEARMHEAD_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArm.h"

namespace VioletVreath {

/**
 * 敵機エルミオネの触手の頭 .
 * グラの触手に挑戦ッッ！！！
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArmHead : public EnemyErmioneArm {

public:
    GgafLib::LaserChipDepository* pDepo_laser_chip_;
public:
    EnemyErmioneArmHead(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void processBehavior() override;

    void processChangeGeoFinal() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    virtual ~EnemyErmioneArmHead();
};

}
#endif /*ENEMYERMIONEARMHEAD_H_*/

