#include "FormationRis002.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/spline/FixedVelocitySplineVecDriverLeader.h"
#include "jp/ggaf/dx/util/spline/FixedVelocitySplineManufacture.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ris/EnemyRis.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationRis002::FormationRis002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationRis002";
    num_Ris_         = RF_FormationRis002_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationRis002_LaunchInterval(G_RANK);   //リスの間隔(frame)
    velo_mv_         = RF_FormationRis002_MvVelo(G_RANK); //速度
    //スプライン移動の定義
    pSplSrcConnection_ = connectToSplineSourceManager("Spl_00202_");
    pConn_depo_ = connectToDepositoryManager("Shot002");
    pManufacture_ =  NEW FixedVelocitySplineManufacture(pSplSrcConnection_->peek(), 10000);
    //リス編隊作成
    for (int i = 0; i < num_Ris_; i++) {
        EnemyRis* pRis = NEW EnemyRis("Ris01");
        //スプライン移動プログラム設定
        SplineLeader* pProgram = NEW FixedVelocitySplineVecDriverLeader(pManufacture_, pRis->callVecDriver());
        pRis->config(pProgram, pConn_depo_->peek(), nullptr);
        appendFormationMember(pRis);
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
            pRis->setPosition(MyShip::lim_x_behaind_ - 500000, 0, MyShip::lim_z_right_ * 0.8);
            pRis->callVecDriver()->setMvVelo(velo_mv_);
        }
    }
}

void FormationRis002::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationRis002::~FormationRis002() {
    GGAF_DELETE(pManufacture_);
    pSplSrcConnection_->close();
    pConn_depo_->close();
}
