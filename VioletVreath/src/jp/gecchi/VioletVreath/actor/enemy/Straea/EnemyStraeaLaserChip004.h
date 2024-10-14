#ifndef ENEMYSTRAEALASERCHIP004_H_
#define ENEMYSTRAEALASERCHIP004_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip004 : public VvEnemyActor<GgafLib::HomingLaserChip> {

public:
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader_;
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

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    virtual ~EnemyStraeaLaserChip004();

};

}
#endif /*ENEMYSTRAEALASERCHIP004_H_*/

