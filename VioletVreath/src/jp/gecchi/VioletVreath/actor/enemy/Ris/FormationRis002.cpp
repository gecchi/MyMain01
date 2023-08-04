#include "FormationRis002.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveLocoVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ris/EnemyRis.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationRis002::FormationRis002(const char* prm_name) :
        VvFormationActor<TreeFormation>(prm_name, StatusReset(FormationRis002) ) {
    _class_name = "FormationRis002";
    num_Ris_         = 0;
    interval_frames_ = 0;
    velo_mv_         = 0;
    //カーブ移動の定義
    pCurveSrcConnection_ = connectToCurveSourceManager("Spl_00202_");
    pConn_depo_ = connectToDepositoryManager("Shot002");
    pManufacture_ =  NEW FixedVelocityCurveManufacture(pCurveSrcConnection_->peek(), 10000);
    //リス編隊作成
    for (int i = 0; i < RF_FormationRis002_Num(G_MAX_RANK); i++) {
        EnemyRis* pRis = NEW EnemyRis("Ris01");
        //カーブ移動プログラム設定
        VehicleLeader* pVehicleLeader = NEW FixedVelocityCurveLocoVehicleLeader(pManufacture_, pRis->getLocoVehicle());
        pRis->config(pVehicleLeader, pConn_depo_->peek(), nullptr);
        appendFormationMember(pRis);
    }
}

void FormationRis002::initialize() {
}

void FormationRis002::onActive() {
    num_Ris_         = RF_FormationRis002_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationRis002_LaunchInterval(G_RANK);   //リスの間隔(frame)
    velo_mv_         = RF_FormationRis002_MvVelo(G_RANK); //速度
}

void FormationRis002::processBehavior() {
    if (canCalledUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyRis* pRis = (EnemyRis*)calledUpMember(num_Ris_);
        if (pRis) {
            pRis->setPosition(MyShip::lim_x_behaind_ - 500000, 0, MyShip::lim_z_right_ * 0.8);
            pRis->getLocoVehicle()->setMvVelo(velo_mv_);
        }
    }
}

FormationRis002::~FormationRis002() {
    GGAF_DELETE(pManufacture_);
    pCurveSrcConnection_->close();
    pConn_depo_->close();
}
