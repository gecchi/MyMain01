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
    pSplLineCon_ = connectToSplineLineManager("SpConn_00202_");
    pDepoCon_ = connectToDepositoryManager("Conn_Shot002", nullptr);
    //イリス編隊作成
    for (int i = 0; i < num_Iris_; i++) {
        EnemyIris* pIris = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = NEW FixedVelocitySplineSequence(
                                         pIris->_pKurokoA, pSplLineCon_->fetch(), 10000); //移動速度固定
        pIris->config(pProgram, pDepoCon_->fetch(), nullptr);
        addFormationMember(pIris);
    }
}

void FormationIris002::initialize() {
}

void FormationIris002::onActive() {
}

void FormationIris002::processBehavior() {
    if (canCallUp() && (getActivePartFrame()-1) % interval_frames_ == 0) {
        EnemyIris* pIris = (EnemyIris*)callUp();
        if (pIris) {
            pIris->locate(MyShip::lim_behaind_ - 500000, 0, MyShip::lim_zright_ * 0.8);
            pIris->_pKurokoA->setMvVelo(velo_mv_);
            pIris->activate();
        }
    }
}

void FormationIris002::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationIris002::~FormationIris002() {
    pSplLineCon_->close();
    pDepoCon_->close();
}
