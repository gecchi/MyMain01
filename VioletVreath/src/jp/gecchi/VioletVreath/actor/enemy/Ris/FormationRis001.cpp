#include "FormationRis001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveLocusVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ris/EnemyRis.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationRis001::FormationRis001(const char* prm_name) : VvFormationActor<TreeFormation>(prm_name, StatusReset(FormationRis001) ) {
    _class_name = "FormationRis001";
    num_Ris_         = 1;
    interval_frames_ = 1;
    velo_mv_         = 1;
    //リス編隊作成
    pCurveSrcConnection_ = connectToCurveSourceManager("Spl_00201_"); //曲線移動の情報
    pConn_depo_ = connectToDepositoryManager("Shot001");
    pManufacture_ = NEW FixedVelocityCurveManufacture(pCurveSrcConnection_->peek(), 10000);
    int max_num_Ris = RF_FormationRis001_Num(G_MAX_RANK);    //最大編隊数準備
    for (int i = 0; i < max_num_Ris; i++) {
        EnemyRis* pRis = NEW EnemyRis("Ris01");
        //カーブ移動プログラム設定
        VehicleLeader* pVehicleLeader = NEW FixedVelocityCurveLocusVehicleLeader(pManufacture_, pRis->getLocusVehicle()); //移動速度固定
        pRis->config(pVehicleLeader, pConn_depo_->peek(), nullptr);
        appendFormationMember(pRis);
    }
}

void FormationRis001::initialize() {
    num_Ris_         = RF_FormationRis001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationRis001_LaunchInterval(G_RANK);   //リスの間隔(frame)
    velo_mv_         = RF_FormationRis001_MvVelo(G_RANK); //速度
}

void FormationRis001::onActive() {
}

void FormationRis001::processBehavior() {
    if (canCalledUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyRis* pRis = (EnemyRis*)calledUpMember(num_Ris_);
        if (pRis) {
            pRis->setPosition(MyShip::lim_x_behaind_ - 500000, 0, MyShip::lim_z_left_ * 0.8);
            pRis->getLocusVehicle()->setMvVelo(velo_mv_);
        }
    }
}

FormationRis001::~FormationRis001() {
    GGAF_DELETE(pManufacture_);
    pCurveSrcConnection_->close();
    pConn_depo_->close();
}
