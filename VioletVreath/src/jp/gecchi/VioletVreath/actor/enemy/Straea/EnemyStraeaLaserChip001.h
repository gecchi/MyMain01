#ifndef ENEMYSTRAEALASERCHIP001_H_
#define ENEMYSTRAEALASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip001 : public GgafLib::HomingLaserChip {

public:
    EnemyStraeaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyStraeaLaserChip001();

};

}
#endif /*ENEMYSTRAEALASERCHIP001_H_*/

