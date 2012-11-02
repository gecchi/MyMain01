#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas002::FormationPallas002(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationPallas002";
    num_Pallas_      = RR_FormationPallas002_Num(_RANK_);  //編隊数
    interval_frames_ = RR_FormationPallas002_LaunchInterval(_RANK_);  //パラスの間隔(frame)
    velo_mv_         = RR_FormationPallas002_MvVelo(_RANK_); //速度
    //パラス編隊作成
    pSplManufCon_ = connectToSplineManufactureManager("Pallas02");
//    pSplLineCon_     = connectToSplineLineManager("SpConn_Pallas01"); //スプライン定義
    //pDepoCon_ = connectToDepositoryManager("Conn_Shot002", NULL);
    pDepoCon_ = NULL;
    papPallas_ = NEW EnemyPallas*[num_Pallas_];
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = pSplManufCon_->fetch()->createSplineSequence(papPallas_[i]->_pKurokoA); //移動速度固定
        papPallas_[i]->config(pProgram, NULL, NULL);
        //papPallas_[i]->setDepository_Shot(pDepoCon_->fetch()); //弾設定
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

void FormationPallas002::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    GgafDxGeometricActor* pActor_LastDestroyed = (GgafDxGeometricActor*)prm_pActor_LastDestroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_LastDestroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_LastDestroyed);
}

FormationPallas002::~FormationPallas002() {
    pSplManufCon_->close();
    if (pDepoCon_) {
        pDepoCon_->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(papPallas_);
}
