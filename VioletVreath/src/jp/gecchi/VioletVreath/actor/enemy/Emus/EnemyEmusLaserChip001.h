#ifndef ENEMYEMUSLASERCHIP001_H_
#define ENEMYEMUSLASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

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

