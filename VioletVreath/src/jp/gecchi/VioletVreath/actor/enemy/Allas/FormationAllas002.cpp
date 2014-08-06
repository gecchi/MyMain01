#include "stdafx.h"
#include "FormationAllas002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/EnemyAllas.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas002::FormationAllas002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAllas002";
    num_Allas_      = RF_FormationAllas002_Num(G_RANK);  //編隊数
    interval_frames_ = RF_FormationAllas002_LaunchInterval(G_RANK);  //アラスの間隔(frame)
    velo_mv_         = RF_FormationAllas002_MvVelo(G_RANK); //速度
    //アラス編隊作成
    pConn_pSplManuf_ = getConnection_SplineManufactureManager("Allas02");
//    pSplLineConnection_     = getConnection_SplineLineManager("Spl_Allas01"); //スプライン定義
    //pConn_depo_ = getConnection_DepositoryManager("Shot002");
    pConn_depo_ = nullptr;
    papAllas_ = NEW EnemyAllas*[num_Allas_];
    for (int i = 0; i < num_Allas_; i++) {
        papAllas_[i] = NEW EnemyAllas("Allas01");
        //スプライン移動プログラム設定
        SplineKurokoLeader* pProgram = pConn_pSplManuf_->peek()->createKurokoLeader(papAllas_[i]->getKuroko()); //移動速度固定
        papAllas_[i]->config(pProgram, nullptr, nullptr);
        //papAllas_[i]->setDepository_Shot(pConn_depo_->peek()); //弾設定
        papAllas_[i]->inactivate();
        addFormationMember(papAllas_[i]);
    }
}

void FormationAllas002::onActive() {
    for (int i = 0; i < num_Allas_; i++) {
        papAllas_[i]->position(MyShip::lim_x_behaind_ *2 , P_MYSHIP->_y+300000,  P_MYSHIP->_z);
        papAllas_[i]->getKuroko()->setMvVelo(velo_mv_);
        papAllas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

void FormationAllas002::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationAllas002::~FormationAllas002() {
    pConn_pSplManuf_->close();
    if (pConn_depo_) {
        pConn_depo_->close();
    }
    GGAF_DELETEARR(papAllas_);
}
