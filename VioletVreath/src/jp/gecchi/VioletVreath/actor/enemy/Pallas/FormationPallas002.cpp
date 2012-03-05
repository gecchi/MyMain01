#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas002::FormationPallas002(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationPallas002";
    num_Pallas_      = R_FormationPallas002_Num;  //編隊数
    interval_frames_ = R_FormationPallas002_LaunchInterval;  //パラスの間隔(frame)
    velo_mv_         = R_FormationPallas002_MvVelo; //速度
    //パラス編隊作成
    pSplManufCon_ = connectSplineManufactureManager("Pallas02");
//    pSplLineCon_     = connectToSplineLineManager("SpCon_Pallas01"); //スプライン定義
    //pDepoCon_ = connectToDepositoryManager("DpCon_Shot002", NULL);
    pDepoCon_ = NULL;
    papPallas_ = NEW EnemyPallas*[num_Pallas_];
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = pSplManufCon_->use()->createSplineSequence(papPallas_[i]->_pKurokoA); //移動速度固定
        papPallas_[i]->config(pProgram, NULL, NULL);
        //papPallas_[i]->setDepository_Shot(pDepoCon_->use()); //弾設定
        papPallas_[i]->inactivateImmed();
        addSubLast(papPallas_[i]);
    }
}

void FormationPallas002::onActive() {
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i]->locate(MyShip::lim_behaind_ *2 , P_MYSHIP->_Y+300000,  P_MYSHIP->_Z);
        papPallas_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papPallas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

FormationPallas002::~FormationPallas002() {
    pSplManufCon_->close();
    if (pDepoCon_) {
        pDepoCon_->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(papPallas_);
}
