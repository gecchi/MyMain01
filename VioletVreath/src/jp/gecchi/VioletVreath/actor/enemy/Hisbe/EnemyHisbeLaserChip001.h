#ifndef ENEMYHISBELASERCHIP001_H_
#define ENEMYHISBELASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

/**
 * �G�@�q�Y�r�[�̃��[�U�[�`�b�v����1 .
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyHisbeLaserChip001 : public GgafLib::HomingLaserChip {

public:
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    GgafLib::DefaultScene* pNearestScrollingScene_;

public:
    EnemyHisbeLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyHisbeLaserChip001();

};

}
#endif /*ENEMYHISBELASERCHIP001_H_*/

