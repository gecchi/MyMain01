#ifndef ENEMYRATISLAVIAEYESTRAIGHTLASERCHIP001_H_
#define ENEMYRATISLAVIAEYESTRAIGHTLASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

class EnemyRatislaviaEyeStraightLaserChip001 : public VvEnemyActor<GgafLib::StraightLaserChip> {

public:
    EnemyRatislaviaEyeStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~EnemyRatislaviaEyeStraightLaserChip001();

};

}
#endif /*ENEMYRATISLAVIAEYESTRAIGHTLASERCHIP001_H_*/

