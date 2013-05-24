#ifndef ENEMYASTRAEALASERCHIP001_H_
#define ENEMYASTRAEALASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyAstraeaLaserChip001 : public GgafLib::HomingLaserChip {

public:
    EnemyAstraeaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyAstraeaLaserChip001();

};

}
#endif /*ENEMYASTRAEALASERCHIP001_H_*/

