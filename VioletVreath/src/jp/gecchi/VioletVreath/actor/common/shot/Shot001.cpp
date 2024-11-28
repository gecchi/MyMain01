#include "Shot001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveLocusVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/manager/CurveSourceManagerEx.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

Shot001::Shot001(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Flora", StatusReset(Shot001)) {
    _class_name = "Shot001";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pCurveManufConn_ = connectToCurveManufactureManager("Shot001_curve");
    pVehicleLeader_ = createCurveVehicleLeader(pCurveManufConn_->peek());
}

void Shot001::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
    setScale(2000);
    getScaler()->setRange(2000, 3000);
}

void Shot001::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setMvVelo(RF_Shot001_MvVelo(G_RANK));    //移動速度
    pLocusVehicle->setRollFaceAngVelo(RF_Shot001_AngVelo(G_RANK)); //きりもみ具合
    pVehicleLeader_->start(RELATIVE_COORD_DIRECTION);
    getScaler()->beat(30,5,0,2,-1);
//    _TRACE_(FUNC_NAME<<" id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getLocusVehicle()->_rz_mv<<"\t"<<getLocusVehicle()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processBehavior() {
//    _TRACE_(FUNC_NAME<<" before id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getLocusVehicle()->_rz_mv<<"\t"<<getLocusVehicle()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    //座標に反映
    pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作
    pLocusVehicle->behave();
    getScaler()->behave();
//    _TRACE_(FUNC_NAME<<" after id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getLocusVehicle()->_rz_mv<<"\t"<<getLocusVehicle()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot001::onInactive() {
}


Shot001::~Shot001() {
    pCurveManufConn_->close();
    GGAF_DELETE(pVehicleLeader_);

}
