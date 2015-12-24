#ifndef ENEMYWATERINGLASERCHIP001_H_
#define ENEMYWATERINGLASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

/**
 * �I�v�V�������[�U�[�̃`�b�v .
 * WateringLaserChip �� ���b�N�I���@�\��ǉ��B
 * (WateringLaserChip���番������)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class EnemyWateringLaserChip001 : public GgafLib::WateringLaserChip {

public:
    EnemyWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyWateringLaserChip001();

};

}
#endif /*ENEMYWATERINGLASERCHIP001_H_*/

