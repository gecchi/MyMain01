#ifndef ENEMYESPERIALASERCHIP001_H_
#define ENEMYESPERIALASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

class EnemyEsperiaLaserChip001 : public GgafLib::HomingLaserChip {

public:
    enum {
        PROG_MOVE_UP,
        PROG_TURN1,
        PROG_TURN2,
        PROG_INTO_MYSHIP,
        PROG_NOTHING,
        PROG_BANPEI,
    };
    enum {
        SE_FIRE,
    };
    /** 発射時のY座標 */
    coord begin_y_;
    /** 屈折までのY軸方向距離 */
    coord turn_dy_;
    /** 目標座標1(屈折ポイント) */
    coord tx1_, ty1_, tz1_;
    /** 目標座標2(自機周りの到達ポイント) */
    coord tx2_, ty2_, tz2_;

public:
    EnemyEsperiaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyEsperiaLaserChip001();

};

}
#endif /*ENEMYESPERIALASERCHIP001_H_*/

