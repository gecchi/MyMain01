#ifndef ENEMYHISBELASERCHIP001_H_
#define ENEMYHISBELASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

/**
 * �G�@�q�Y�r�[�̃��[�U�[�`�b�v����1 .
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyHisbeLaserChip001 : public VvEnemyActor<GgafLib::HomingLaserChip> {

public:
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader_;
    GgafLib::DefaultScene* pFeatureScene_;

public:
    EnemyHisbeLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onInactive() override;
    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void processJudgement() override;

    virtual ~EnemyHisbeLaserChip001();

};

}
#endif /*ENEMYHISBELASERCHIP001_H_*/

