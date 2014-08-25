#ifndef ENEMYOZARTIALASERCHIP01_H_
#define ENEMYOZARTIALASERCHIP01_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

class EnemyOzartiaLaserChip01 : public GgafLib::StraightLaserChip {

public:

    EnemyOzartiaLaserChip01(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyOzartiaLaserChip01();

};

}
#endif /*ENEMYOZARTIALASERCHIP01_H_*/

