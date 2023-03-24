#ifndef ENEMYEMUSLASERCHIP001_H_
#define ENEMYEMUSLASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

/**
 * エムス用レーザーチップ .
 * 汎用レーザーに切り替えたので現在未使用
 */
class EnemyEmusLaserChip001 : public VvEnemyActor<GgafLib::WateringLaserChip> {

public:
    EnemyEmusLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyEmusLaserChip001();

};

}
#endif /*ENEMYEMUSLASERCHIP001_H_*/

