#ifndef ENEMYSTRAEALASERCHIP004_H_
#define ENEMYSTRAEALASERCHIP004_H_
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip004 : public GgafLib::HomingLaserChip {

public:
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
//    static GgafDxCore::GgafDxTextureConnection* pTexCon1_;
//    static GgafDxCore::GgafDxTextureConnection* pTexCon2_;

public:
    EnemyStraeaLaserChip004(const char* prm_name);

    void initialize() override;
    void onCreateModel() override;

    void onActive() override;
    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyStraeaLaserChip004();

};

}
#endif /*ENEMYSTRAEALASERCHIP004_H_*/

