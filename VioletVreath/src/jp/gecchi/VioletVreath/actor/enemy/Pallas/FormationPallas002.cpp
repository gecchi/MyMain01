#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas002::FormationPallas002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationPallas002";
    num_Pallas_      = RR_FormationPallas002_Num(_RANK_);  //編隊数
    interval_frames_ = RR_FormationPallas002_LaunchInterval(_RANK_);  //パラスの間隔(frame)
    velo_mv_         = RR_FormationPallas002_MvVelo(_RANK_); //速度
    //パラス編隊作成
    pSplManufConnection_ = connectToSplineManufactureManager("Pallas02");
//    pSplLineConnection_     = connectToSplineLineManager("Spl_Pallas01"); //スプライン定義
    //pDepoConnection_ = connectToDepositoryManager("Shot002");
    pDepoConnection_ = nullptr;
    papPallas_ = NEW EnemyPallas*[num_Pallas_];
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = pSplManufConnection_->peek()->createSplineSequence(papPallas_[i]->_pKurokoA); //移動速度固定
        papPallas_[i]->config(pProgram, nullptr, nullptr);
        //papPallas_[i]->setDepository_Shot(pDepoConnection_->peek()); //弾設定
        papPallas_[i]->inactivateImmed();
        addFormationMember(papPallas_[i]);
    }
}

void FormationPallas002::onActive() {
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i]->locate(MyShip::lim_behaind_ *2 , P_MYSHIP->_Y+300000,  P_MYSHIP->_Z);
        papPallas_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papPallas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

void FormationPallas002::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（※ボーナススコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationPallas002::~FormationPallas002() {
    pSplManufConnection_->close();
    if (pDepoConnection_) {
        pDepoConnection_->close();
    }
    GGAF_DELETEARR(papPallas_);
}
