#include "stdafx.h"
#include "FormationIris001.h"


#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/EnemyIris.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris001::FormationIris001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationIris001";
    num_Iris_        = RF_FormationIris001_Num(_RANK_);    //編隊数
    interval_frames_ = RF_FormationIris001_LaunchInterval(_RANK_);   //イリスの間隔(frame)
    velo_mv_         = RF_FormationIris001_MvVelo(_RANK_); //速度
    //イリス編隊作成
    pSplLineConnection_ = connectToSplineLineManager("Spl_00201_"); //スプライン定義
    pDepoConnection_ = connectToDepositoryManager("Shot001");
    for (int i = 0; i < num_Iris_; i++) {
        EnemyIris* pIris = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        SplineKurokoLeader* pProgram = NEW FixedVelocitySplineKurokoLeader(
                                         pIris->_pKurokoA, pSplLineConnection_->peek(), 10000); //移動速度固定
        pIris->config(pProgram, pDepoConnection_->peek(), nullptr);
        addFormationMember(pIris);
    }
}

void FormationIris001::initialize() {
}

void FormationIris001::onActive() {
}

void FormationIris001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyIris* pIris = (EnemyIris*)callUpMember();
        if (pIris) {
            pIris->locate(MyShip::lim_X_behaind_ - 500000, 0, MyShip::lim_Z_left_ * 0.8);
            pIris->_pKurokoA->setMvVelo(velo_mv_);
        }
    }
}

void FormationIris001::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationIris001::~FormationIris001() {
    pSplLineConnection_->close();
    pDepoConnection_->close();
}
