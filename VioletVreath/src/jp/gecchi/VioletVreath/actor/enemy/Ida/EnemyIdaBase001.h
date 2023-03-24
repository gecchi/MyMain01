#ifndef ENEMYIDABASE001_H_
#define ENEMYIDABASE001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/EnemyIdaBase.h"

namespace VioletVreath {

/**
 * 敵機イーダの基盤その１ .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIdaBase001 : public EnemyIdaBase {

public:
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIdaBase001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~EnemyIdaBase001();
};

}
#endif /*ENEMYIDABASE_H_*/

