#include "stdafx.h"
#include "FormationHebe.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/EnemyHebe.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe::FormationHebe(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationHebe";

    pConn_HebeDepo_ = connect_DepositoryManager("EnemyHebe4Formation");
    setFormationMember(pConn_HebeDepo_->peek());

    //pConn_ShotDepo_ = connect_DepositoryManager("Shot004"); //Hebeの弾;
    pConn_ShotDepo_ = nullptr;
    updateRankParameter();
}

void FormationHebe::updateRankParameter() {
    RV_NumFormation_     = RF_FormationHebe_Num(G_RANK);            //編隊数
    RV_IntervalFrames_   = RF_FormationHebe_LaunchInterval(G_RANK); //ヘーベの間隔(frame)
    RV_MvVelo_           = RF_FormationHebe_MvVelo(G_RANK);         //速度
}

void FormationHebe::initialize() {
}

void FormationHebe::onActive() {
    updateRankParameter();
}

void FormationHebe::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RV_IntervalFrames_ == 0)) {
        EnemyHebe* pHebe = (EnemyHebe*)callUpMember(RV_NumFormation_);
        if (pHebe) {
            SplineKurokoLeader* pKurokoLeader = getSplManuf()->createKurokoLeader(pHebe->_pKurokoA);
            GgafActorDepository* pDepo_Shot = pConn_ShotDepo_ ? pConn_ShotDepo_->peek() : nullptr;
            pHebe->config(pKurokoLeader, pDepo_Shot, nullptr);
            pHebe->_pKurokoA->setMvVelo(RV_MvVelo_);
            onCallUpHebe(pHebe); //下位フォーメーションクラス個別実装の処理
        }
    }
}

void FormationHebe::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationHebe::~FormationHebe() {
    pConn_HebeDepo_->close();
    if (pConn_ShotDepo_) {
        pConn_ShotDepo_->close();
    }
}

