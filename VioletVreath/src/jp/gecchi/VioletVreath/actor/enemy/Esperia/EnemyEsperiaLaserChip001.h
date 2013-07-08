#ifndef ENEMYESPERIALASERCHIP001_H_
#define ENEMYESPERIALASERCHIP001_H_
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
    };
    enum {
        SE_FIRE,
    };
    /** 発射時のY座標 */
    coord begin_Y_;
    /** 屈折までのY軸方向距離 */
    coord turn_dY_;
    /** 目標座標1(屈折ポイント) */
    coord tX1_, tY1_, tZ1_;
    /** 目標座標2(自機周りの到達ポイント) */
    coord tX2_, tY2_, tZ2_;

public:
    EnemyEsperiaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyEsperiaLaserChip001();

};

}
#endif /*ENEMYESPERIALASERCHIP001_H_*/

