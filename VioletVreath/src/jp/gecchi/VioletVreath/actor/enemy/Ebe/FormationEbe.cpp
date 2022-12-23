#include "FormationEbe.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ebe/EnemyEbe.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationEbe::FormationEbe(const char* prm_name, const char* prm_ldr_id)
   : DepositoryFormation(prm_name, SEC_F(20)) {
    _class_name = "FormationEbe";

    pConn_pEbeDepo_ = connectToDepositoryManager("EnemyEbe4Formation");
    setFormationMember(pConn_pEbeDepo_->peek());

    pConn_pShotDepo_ = nullptr;
    updateRankParameter();
}

void FormationEbe::updateRankParameter() {
    RV_Num_              = RF_FormationEbe_Num(G_RANK);            //編隊数
    RV_LaunchInterval    = RF_FormationEbe_LaunchInterval(G_RANK); //エーベの間隔(frame)
    RV_MvVelo_           = RF_FormationEbe_MvVelo(G_RANK);         //速度
}

void FormationEbe::initialize() {
}

void FormationEbe::onActive() {
    updateRankParameter();
}

void FormationEbe::processBehavior() {
    if (canCalledUp() && (getActiveFrame() % RV_LaunchInterval == 0)) {
        EnemyEbe* pEbe = (EnemyEbe*)calledUpMember(RV_Num_);
        if (pEbe) {
            GgafCore::ActorDepository* pDepo_shot = pConn_pShotDepo_ ? pConn_pShotDepo_->peek() : nullptr;
            pEbe->config(getSplManuf(), pDepo_shot, nullptr);
            pEbe->getVecVehicle()->setMvVelo(RV_MvVelo_);
            onCalledUpEbe(pEbe); //下位フォーメーションクラス個別実装の処理
        }
    }
}

void FormationEbe::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationEbe::~FormationEbe() {
    pConn_pEbeDepo_->close();
    if (pConn_pShotDepo_) {
        pConn_pShotDepo_->close();
    }
}

