#include "stdafx.h"
#include "FormationRis002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ris/EnemyRis.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationRis002::FormationRis002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationRis002";
    num_Ris_        = RF_FormationRis002_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationRis002_LaunchInterval(G_RANK);   //リスの間隔(frame)
    velo_mv_         = RF_FormationRis002_MvVelo(G_RANK); //速度
    //スプライン移動の定義
    pSplLineConnection_ = connect_SplineLineManager("Spl_00202_");
    pDepoConnection_ = connect_DepositoryManager("Shot002");
    //リス編隊作成
    for (int i = 0; i < num_Ris_; i++) {
        EnemyRis* pRis = NEW EnemyRis("Ris01");
        //スプライン移動プログラム設定
        SplineKurokoLeader* pProgram = NEW FixedVelocitySplineKurokoLeader(
                                         pRis->_pKurokoA, pSplLineConnection_->peek(), 10000); //移動速度固定
        pRis->config(pProgram, pDepoConnection_->peek(), nullptr);
        addFormationMember(pRis);
    }
}

void FormationRis002::initialize() {
}

void FormationRis002::onActive() {
}

void FormationRis002::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyRis* pRis = (EnemyRis*)callUpMember();
        if (pRis) {
            pRis->position(MyShip::lim_x_behaind_ - 500000, 0, MyShip::lim_z_right_ * 0.8);
            pRis->_pKurokoA->setMvVelo(velo_mv_);
        }
    }
}

void FormationRis002::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationRis002::~FormationRis002() {
    pSplLineConnection_->close();
    pDepoConnection_->close();
}
