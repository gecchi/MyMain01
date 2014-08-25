#ifndef ENEMYEMUSLASERCHIP001_H_
#define ENEMYEMUSLASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

/**
 * エムス用レーザーチップ .
 * 汎用レーザーに切り替えたので現在未使用
 */
class EnemyEmusLaserChip001 : public GgafLib::WateringLaserChip {

public:
    EnemyEmusLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyEmusLaserChip001();

};

}
#endif /*ENEMYEMUSLASERCHIP001_H_*/

