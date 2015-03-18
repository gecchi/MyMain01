#ifndef ENEMYSTRAEALASERCHIP004_H_
#define ENEMYSTRAEALASERCHIP004_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip004 : public GgafLib::HomingLaserChip {

public:
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
//    static GgafDxCore::GgafDxTextureConnection* pTexCon1_;
//    static GgafDxCore::GgafDxTextureConnection* pTexCon2_;

public:
    EnemyStraeaLaserChip004(const char* prm_name);

    void initialize() override;
    void onCreateModel() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyStraeaLaserChip004();

};

}
#endif /*ENEMYSTRAEALASERCHIP004_H_*/

