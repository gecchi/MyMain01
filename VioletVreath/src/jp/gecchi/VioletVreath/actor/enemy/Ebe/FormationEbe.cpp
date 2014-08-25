#include "FormationEbe.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/EnemyEbe.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEbe::FormationEbe(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEbe";

    pConn_pEbeDepo_ = getConnection_DepositoryManager("EnemyEbe4Formation");
    setFormationMember(pConn_pEbeDepo_->peek());

    pConn_pShotDepo_ = nullptr;
    updateRankParameter();
}

void FormationEbe::updateRankParameter() {
    RV_NumFormation_     = RF_FormationEbe_Num(G_RANK);            //�ґ���
    RV_IntervalFrames_   = RF_FormationEbe_LaunchInterval(G_RANK); //�G�[�x�̊Ԋu(frame)
    RV_MvVelo_           = RF_FormationEbe_MvVelo(G_RANK);         //���x
}

void FormationEbe::initialize() {
}

void FormationEbe::onActive() {
    updateRankParameter();
}

void FormationEbe::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RV_IntervalFrames_ == 0)) {
        EnemyEbe* pEbe = (EnemyEbe*)callUpMember(RV_NumFormation_);
        if (pEbe) {
            SplineKurokoLeader* pKurokoLeader = getSplManuf()->createKurokoLeader(pEbe->getKuroko());
            GgafActorDepository* pDepo_shot = pConn_pShotDepo_ ? pConn_pShotDepo_->peek() : nullptr;
            pEbe->config(pKurokoLeader, pDepo_shot, nullptr);
            pEbe->getKuroko()->setMvVelo(RV_MvVelo_);
            onCallUpEbe(pEbe); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
        }
    }
}

void FormationEbe::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationEbe::~FormationEbe() {
    pConn_pEbeDepo_->close();
    if (pConn_pShotDepo_) {
        pConn_pShotDepo_->close();
    }
}

