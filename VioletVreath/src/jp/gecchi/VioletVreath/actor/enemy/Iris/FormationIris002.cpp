#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris002::FormationIris002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationIris002";
    num_Iris_        = RR_FormationIris002_Num(_RANK_);    //編隊数
    interval_frames_ = RR_FormationIris002_LaunchInterval(_RANK_);   //イリスの間隔(frame)
    velo_mv_         = RR_FormationIris002_MvVelo(_RANK_); //速度
    //スプライン移動の定義
    pSplLineConnection_ = connectToSplineLineManager("Spl_00202_");
    pDepoConnection_ = connectToDepositoryManager("Shot002");
    //イリス編隊作成
    for (int i = 0; i < num_Iris_; i++) {
        EnemyIris* pIris = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        SplineKurokoStepper* pProgram = NEW FixedVelocitySplineKurokoStepper(
                                         pIris->_pKurokoA, pSplLineConnection_->peek(), 10000); //移動速度固定
        pIris->config(pProgram, pDepoConnection_->peek(), nullptr);
        addFormationMember(pIris);
    }
}

void FormationIris002::initialize() {
}

void FormationIris002::onActive() {
}

void FormationIris002::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyIris* pIris = (EnemyIris*)callUpMember();
        if (pIris) {
            pIris->locate(MyShip::lim_behaind_ - 500000, 0, MyShip::lim_zright_ * 0.8);
            pIris->_pKurokoA->setMvVelo(velo_mv_);
        }
    }
}

void FormationIris002::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（※ボーナススコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationIris002::~FormationIris002() {
    pSplLineConnection_->close();
    pDepoConnection_->close();
}
