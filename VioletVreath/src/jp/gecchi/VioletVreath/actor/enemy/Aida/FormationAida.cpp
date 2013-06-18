#include "stdafx.h"
#include "FormationAida.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/EnemyAida.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAida::FormationAida(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationAida";

    pConne_AidaDepo_ = connectToDepositoryManager("EnemyAida4Formation");
    setFormationMember(pConne_AidaDepo_->peek());

    //pConne_ShotDepo_ = connectToDepositoryManager("Shot004"); //Aidaの弾;
    pConne_ShotDepo_ = nullptr;
    updateRankParameter();
}

void FormationAida::updateRankParameter() {
    RV_NumFormation_     = 2;
    RV_IntervalFrames_   = 2;
    RV_MvVelo_           = 3;
}

void FormationAida::initialize() {
}

void FormationAida::onActive() {
    updateRankParameter();
}

void FormationAida::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RV_IntervalFrames_ == 0)) {
        EnemyAida* pAida = (EnemyAida*)callUpMember(RV_NumFormation_);
        if (pAida) {
            SplineKurokoLeader* pKurokoLeader = getSplManuf()->createKurokoLeader(pAida->_pKurokoA);
            GgafActorDepository* pDepo_Shot = pConne_ShotDepo_ ? pConne_ShotDepo_->peek() : nullptr;
            pAida->_pKurokoA->setMvVelo(RV_MvVelo_);
            onCallUpAida(pAida); //下位フォーメーションクラス個別実装の処理
        }
    }
}

void FormationAida::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationAida::~FormationAida() {
    pConne_AidaDepo_->close();
    if (pConne_ShotDepo_) {
        pConne_ShotDepo_->close();
    }
}

