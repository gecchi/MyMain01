#include "stdafx.h"
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

    pConn_EbeDepo_ = connect_DepositoryManager("EnemyEbe4Formation");
    setFormationMember(pConn_EbeDepo_->peek());

    pConn_ShotDepo_ = nullptr;
    updateRankParameter();
}

void FormationEbe::updateRankParameter() {
    RV_NumFormation_     = RF_FormationEbe_Num(G_RANK);            //編隊数
    RV_IntervalFrames_   = RF_FormationEbe_LaunchInterval(G_RANK); //エーベの間隔(frame)
    RV_MvVelo_           = RF_FormationEbe_MvVelo(G_RANK);         //速度
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
            SplineKurokoLeader* pKurokoLeader = getSplManuf()->createKurokoLeader(pEbe->_pKuroko);
            GgafActorDepository* pDepo_Shot = pConn_ShotDepo_ ? pConn_ShotDepo_->peek() : nullptr;
            pEbe->config(pKurokoLeader, pDepo_Shot, nullptr);
            pEbe->_pKuroko->setMvVelo(RV_MvVelo_);
            onCallUpEbe(pEbe); //下位フォーメーションクラス個別実装の処理
        }
    }
}

void FormationEbe::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationEbe::~FormationEbe() {
    pConn_EbeDepo_->close();
    if (pConn_ShotDepo_) {
        pConn_ShotDepo_->close();
    }
}

