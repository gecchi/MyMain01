#include "FormationAllas002.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAllas002::FormationAllas002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAllas002";
    num_Allas_      = RF_FormationAllas002_Num(G_RANK);  //編隊数
    interval_frames_ = RF_FormationAllas002_LaunchInterval(G_RANK);  //アラスの間隔(frame)
    velo_mv_         = RF_FormationAllas002_MvVelo(G_RANK); //速度
    //アラス編隊作成
    pConn_pSplManuf_ = connectToSplineManufactureManager("Allas02");
    pConn_depo_ = nullptr;
    papAllas_ = NEW EnemyAllas*[num_Allas_];
    for (int i = 0; i < num_Allas_; i++) {
        papAllas_[i] = NEW EnemyAllas("Allas01");
        //スプライン移動プログラム設定
        SplineLeader* pProgram = pConn_pSplManuf_->peek()->createRikishaLeader(papAllas_[i]->callRikisha()); //移動速度固定
        papAllas_[i]->config(pProgram, nullptr, nullptr);
        //papAllas_[i]->setDepository_Shot(pConn_depo_->peek()); //弾設定
        appendFormationMember(papAllas_[i]);
    }
}

void FormationAllas002::onActive() {
    for (int i = 0; i < num_Allas_; i++) {
        papAllas_[i]->setPosition(MyShip::lim_x_behaind_ *2 , pMYSHIP->_y+300000,  pMYSHIP->_z);
        papAllas_[i]->callRikisha()->setMvVelo(velo_mv_);
        papAllas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

void FormationAllas002::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationAllas002::~FormationAllas002() {
    pConn_pSplManuf_->close();
    if (pConn_depo_) {
        pConn_depo_->close();
    }
    GGAF_DELETEARR(papAllas_);
}
