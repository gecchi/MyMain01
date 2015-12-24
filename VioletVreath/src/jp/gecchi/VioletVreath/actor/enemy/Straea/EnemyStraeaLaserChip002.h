#ifndef ENEMYSTRAEALASERCHIP002_H_
#define ENEMYSTRAEALASERCHIP002_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip002 : public GgafLib::RefractionLaserChip {

public:
    /** 反射時エフェクトデポジトリへの接続 */
    DepositoryConnection* pConn_pRefractionEffectDepository_;

public:
    EnemyStraeaLaserChip002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onRefractionInto(int prm_num_refraction) override;

    void onRefractionOutOf(int prm_num_refraction) override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyStraeaLaserChip002();

};

}
#endif /*ENEMYSTRAEALASERCHIP002_H_*/

