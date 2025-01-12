#ifndef ENEMYWATERINGLASERCHIP001_H_
#define ENEMYWATERINGLASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

/**
 * オプションレーザーのチップ .
 * WateringLaserChip に ロックオン機能を追加。
 * (WateringLaserChipから分離した)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class EnemyWateringLaserChip001 : public VvEnemyActor<GgafLib::WateringLaserChip> {

public:
    coord tmp_x_, tmp_y_, tmp_z_;

public:
    EnemyWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    virtual ~EnemyWateringLaserChip001();

};

}
#endif /*ENEMYWATERINGLASERCHIP001_H_*/

