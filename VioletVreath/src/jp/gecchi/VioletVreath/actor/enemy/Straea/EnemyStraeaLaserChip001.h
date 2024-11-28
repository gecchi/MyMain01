#ifndef ENEMYSTRAEALASERCHIP001_H_
#define ENEMYSTRAEALASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip001 : public VvEnemyActor<GgafLib::HomingLaserChip> {

public:
    EnemyStraeaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void processJudgement() override;

    virtual ~EnemyStraeaLaserChip001();

};

}
#endif /*ENEMYSTRAEALASERCHIP001_H_*/

