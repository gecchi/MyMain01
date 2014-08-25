#ifndef ENEMYEMUSLASERCHIP001_H_
#define ENEMYEMUSLASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

/**
 * �G���X�p���[�U�[�`�b�v .
 * �ėp���[�U�[�ɐ؂�ւ����̂Ō��ݖ��g�p
 */
class EnemyEmusLaserChip001 : public GgafLib::WateringLaserChip {

public:
    EnemyEmusLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyEmusLaserChip001();

};

}
#endif /*ENEMYEMUSLASERCHIP001_H_*/

