#ifndef ENEMYHESPERIALASERCHIP001_H_
#define ENEMYHESPERIALASERCHIP001_H_
namespace VioletVreath {

class EnemyHesperiaLaserChip001 : public GgafLib::HomingLaserChip {


public:
    enum {
        PROG_MOVE_UP = 1,
        PROG_TURN,
        PROG_INTO_MYSHIP,
        PROG_NOTHING,
    };


    coord tX_, tY_, tZ_;

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

