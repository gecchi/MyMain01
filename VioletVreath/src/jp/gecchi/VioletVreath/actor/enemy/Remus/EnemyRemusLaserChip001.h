#ifndef ENEMYREMUSLASERCHIP001_H_
#define ENEMYREMUSLASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

class EnemyRemusLaserChip001 : public GgafLib::WateringLaserChip {

public:
    EnemyRemusLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyRemusLaserChip001();

};

}
#endif /*ENEMYREMUSLASERCHIP001_H_*/

