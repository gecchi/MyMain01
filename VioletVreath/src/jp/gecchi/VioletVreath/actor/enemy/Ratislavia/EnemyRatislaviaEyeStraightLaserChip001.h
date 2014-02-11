#ifndef ENEMYRATISLAVIAEYESTRAIGHTLASERCHIP001_H_
#define ENEMYRATISLAVIAEYESTRAIGHTLASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

class EnemyRatislaviaEyeStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    EnemyRatislaviaEyeStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyRatislaviaEyeStraightLaserChip001();

};

}
#endif /*ENEMYRATISLAVIAEYESTRAIGHTLASERCHIP001_H_*/

