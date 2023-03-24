#ifndef ENEMYSTRAIGHTLASERCHIP001_H_
#define ENEMYSTRAIGHTLASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

class EnemyStraightLaserChip001 : public VvEnemyActor<GgafLib::StraightLaserChip> {

public:

    EnemyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~EnemyStraightLaserChip001();

};

}
#endif /*ENEMYSTRAIGHTLASERCHIP001_H_*/

