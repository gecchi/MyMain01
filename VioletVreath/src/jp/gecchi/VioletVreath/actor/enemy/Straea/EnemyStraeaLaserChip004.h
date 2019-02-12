#ifndef ENEMYSTRAEALASERCHIP004_H_
#define ENEMYSTRAEALASERCHIP004_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip004 : public GgafLib::HomingLaserChip {

public:
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineLeader* pKurokoLeader_;
//    static GgafDx::TextureConnection* pTexCon1_;
//    static GgafDx::TextureConnection* pTexCon2_;

public:
    EnemyStraeaLaserChip004(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    virtual ~EnemyStraeaLaserChip004();

};

}
#endif /*ENEMYSTRAEALASERCHIP004_H_*/

