#ifndef ENEMYHESPERIALASERCHIP001_H_
#define ENEMYHESPERIALASERCHIP001_H_
namespace VioletVreath {

class EnemyHesperiaLaserChip001 : public GgafLib::HomingLaserChip {

public:
    enum {
        PROG_MOVE_UP = 1,
        PROG_TURN1,
        PROG_TURN2,
        PROG_INTO_MYSHIP,
        PROG_NOTHING,
    };
    enum {
        SE_FIRE = 0,
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
    EnemyHesperiaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyHesperiaLaserChip001();

};

}
#endif /*ENEMYHESPERIALASERCHIP001_H_*/

