#ifndef ENEMYSTRAEALASERCHIP001_H_
#define ENEMYSTRAEALASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip001 : public GgafLib::HomingLaserChip {

public:
    EnemyStraeaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyStraeaLaserChip001();

};

}
#endif /*ENEMYSTRAEALASERCHIP001_H_*/

