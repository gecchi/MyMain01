#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris001::FormationIris001(const char* prm_name) : TreeFormation(prm_name, 30*60) {
    _class_name = "FormationIris001";
    num_Iris_        = RR_FormationIris001_Num(_RANK_);    //編隊数
    interval_frames_ = RR_FormationIris001_LaunchInterval(_RANK_);   //イリスの間隔(frame)
    velo_mv_         = RR_FormationIris001_MvVelo(_RANK_); //速度
    //イリス編隊作成
    pSplLineCon_   = connectToSplineLineManager("SpCon_00201_"); //スプライン定義
    pDepoCon_ = connectToDepositoryManager("DpCon_Shot001", NULL);
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

void FormationIris001::initialize() {
    //編隊作成はonActive()で行わうこと。
    //FormationTableScene で active にされるタイミングは変動するため
}

void FormationIris001::onActive() {
    for (int i = 0; i < num_Iris_; i++) {
        papIris_[i]->locate(MyShip::lim_behaind_ - 500000, 0, MyShip::lim_zleft_ * 0.8);
        papIris_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papIris_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

FormationIris001::~FormationIris001() {
    pSplLineCon_->close();
    pDepoCon_->close();
    DELETEARR_IMPOSSIBLE_NULL(papIris_);
}
