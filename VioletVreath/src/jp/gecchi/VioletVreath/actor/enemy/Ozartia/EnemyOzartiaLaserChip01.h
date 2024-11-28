#ifndef ENEMYOZARTIALASERCHIP01_H_
#define ENEMYOZARTIALASERCHIP01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

class EnemyOzartiaLaserChip01 : public VvEnemyActor<GgafLib::StraightLaserChip> {

public:

    EnemyOzartiaLaserChip01(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processJudgement() override;

    virtual ~EnemyOzartiaLaserChip01();

};

}
#endif /*ENEMYOZARTIALASERCHIP01_H_*/

