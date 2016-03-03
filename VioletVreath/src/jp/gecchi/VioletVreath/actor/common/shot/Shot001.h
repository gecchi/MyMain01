#ifndef SHOT001_H_
#define SHOT001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * �ėp�e001(��) .
 * �j��\�œ��������ړ�<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot001 : public GgafLib::DefaultMassMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �X�v���C����`�����ւ̐ڑ� */
    SplineLineConnection* pSplLineConnection_;

public:
    Shot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Shot001();
};

}
#endif /*SHOT001_H_*/

