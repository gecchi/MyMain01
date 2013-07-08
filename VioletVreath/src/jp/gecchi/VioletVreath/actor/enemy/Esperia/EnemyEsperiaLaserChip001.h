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
    /** ���ˎ���Y���W */
    coord begin_Y_;
    /** ���܂܂ł�Y���������� */
    coord turn_dY_;
    /** �ڕW���W1(���܃|�C���g) */
    coord tX1_, tY1_, tZ1_;
    /** �ڕW���W2(���@����̓��B�|�C���g) */
    coord tX2_, tY2_, tZ2_;

public:
    EnemyEsperiaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyEsperiaLaserChip001();

};

}
#endif /*ENEMYESPERIALASERCHIP001_H_*/

