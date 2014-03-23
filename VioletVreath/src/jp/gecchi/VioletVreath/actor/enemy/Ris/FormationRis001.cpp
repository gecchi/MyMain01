#include "stdafx.h"
#include "FormationRis001.h"


#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ris/EnemyRis.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationRis001::FormationRis001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationRis001";
    num_Ris_        = RF_FormationRis001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationRis001_LaunchInterval(G_RANK);   //リスの間隔(frame)
    velo_mv_         = RF_FormationRis001_MvVelo(G_RANK); //速度
    //リス編隊作成
    pSplLineConnection_ = connect_SplineLineManager("Spl_00201_"); //スプライン定義
    pDepoConnection_ = connect_DepositoryManager("Shot001");
    for (int i = 0; i < num_Ris_; i++) {
        EnemyRis* pRis = NEW EnemyRis("Ris01");
        //スプライン移動プログラム設定
        SplineKurokoLeader* pProgram = NEW FixedVelocitySplineKurokoLeader(
                                         pRis->getKuroko(), pSplLineConnection_->peek(), 10000); //移動速度固定
        pRis->config(pProgram, pDepoConnection_->peek(), nullptr);
        addFormationMember(pRis);
    }
}

void FormationRis001::initialize() {
}

void FormationRis001::onActive() {
}

void FormationRis001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyRis* pRis = (EnemyRis*)callUpMember();
        if (pRis) {
            pRis->position(MyShip::lim_x_behaind_ - 500000, 0, MyShip::lim_z_left_ * 0.8);
            pRis->getKuroko()->setMvVelo(velo_mv_);
        }
    }
}

void FormationRis001::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationRis001::~FormationRis001() {
    pSplLineConnection_->close();
    pDepoConnection_->close();
}
