#include "Shot001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveVecDriverLeader.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/CurveSourceManagerEx.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

Shot001::Shot001(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Flora", StatusReset(Shot001)) {
    _class_name = "Shot001";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_EXPLOSION_002");
    pCurveManufConn_ = connectToCurveManufactureManager("Shot001_curve");
    pDriverLeader_ = NEW FixedVelocityCurveVecDriverLeader(pCurveManufConn_->peek(), getVecDriver()); //移動速度固定
}

void Shot001::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
    setScale(2000);
    getScaler()->setRange(2000, 3000);
}

void Shot001::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setMvVelo(RF_Shot001_MvVelo(G_RANK));    //移動速度
    pVecDriver->setRollFaceAngVelo(RF_Shot001_AngVelo(G_RANK)); //きりもみ具合
    pDriverLeader_->start(RELATIVE_COORD_DIRECTION);
    getScaler()->beat(30,5,0,2,-1);
//    _TRACE_(FUNC_NAME<<" id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getVecDriver()->_rz_mv<<"\t"<<getVecDriver()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processBehavior() {
//    _TRACE_(FUNC_NAME<<" before id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getVecDriver()->_rz_mv<<"\t"<<getVecDriver()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    //座標に反映
    pDriverLeader_->behave(); //カーブ移動するようにDriverを操作
    pVecDriver->behave();
    getScaler()->behave();
//    _TRACE_(FUNC_NAME<<" after id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getVecDriver()->_rz_mv<<"\t"<<getVecDriver()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(0);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    pCurveManufConn_->close();
    GGAF_DELETE(pDriverLeader_);

}
