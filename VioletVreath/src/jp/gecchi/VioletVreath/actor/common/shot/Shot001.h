#ifndef SHOT001_H_
#define SHOT001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * �ėp�e001(��) .
 * �j��\�œ��������ړ�<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot001 : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafDx::SplineLeader* pVecDriverLeader_;
    /** �X�v���C����`�����ւ̐ڑ� */
    GgafDx::SplineManufactureConnection* pSplManufConn_;
public:
    Shot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~Shot001();
};

}
#endif /*SHOT001_H_*/

