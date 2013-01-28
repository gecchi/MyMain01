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
    /** ���ˎ���Y���W */
    coord begin_Y_;
    /** ���܂܂ł�Y���������� */
    coord turn_dY_;
    /** �ڕW���W1(���܃|�C���g) */
    coord tX1_, tY1_, tZ1_;
    /** �ڕW���W2(���@����̓��B�|�C���g) */
    coord tX2_, tY2_, tZ2_;

public:
    EnemyHesperiaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyHesperiaLaserChip001();

};

}
#endif /*ENEMYHESPERIALASERCHIP001_H_*/

