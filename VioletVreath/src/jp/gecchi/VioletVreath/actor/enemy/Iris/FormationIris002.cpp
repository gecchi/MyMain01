#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris002::FormationIris002(const char* prm_name) :
        TreeFormation(prm_name, 30*60) { //30*60後にsayonara()する。早く開放しすぎると Depository の接続が切れるため。
    _class_name = "FormationIris002";
    num_Iris_        = RR_FormationIris002_Num(_RANK_);    //編隊数
    interval_frames_ = RR_FormationIris002_LaunchInterval(_RANK_);   //イリスの間隔(frame)
    velo_mv_         = RR_FormationIris002_MvVelo(_RANK_); //速度
    //スプライン移動の定義
    pSplLineCon_ = connectToSplineLineManager("SpCon_00202_");
    pDepoCon_ = connectToDepositoryManager("DpCon_Shot002", NULL);
    //イリス編隊作成
    papIris_ = NEW EnemyIris*[num_Iris_];
    for (int i = 0; i < num_Iris_; i++) {
        papIris_[i] = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = NEW FixedVelocitySplineSequence(papIris_[i]->_pKurokoA, pSplLineCon_->fetch(), 10000); //移動速度固定
        papIris_[i]->config(pProgram, pDepoCon_->fetch(), NULL);
        papIris_[i]->inactivateImmed();
        addSubLast(papIris_[i]);
    }
}

void FormationIris002::initialize() {

}

void FormationIris002::onActive() {
    for (int i = 0; i < num_Iris_; i++) {
        papIris_[i]->locate(MyShip::lim_behaind_ - 500000, 0, MyShip::lim_zright_ * 0.8);
        papIris_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papIris_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

FormationIris002::~FormationIris002() {
    pSplLineCon_->close();
    pDepoCon_->close();
    DELETEARR_IMPOSSIBLE_NULL(papIris_);
}
