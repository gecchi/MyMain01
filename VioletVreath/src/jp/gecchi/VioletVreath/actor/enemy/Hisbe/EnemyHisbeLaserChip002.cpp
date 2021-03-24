#include "EnemyHisbeLaserChip002.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip002::EnemyHisbeLaserChip002(const char* prm_name) :
        VvEnemyActor<RefractionLaserChip>(prm_name, "HisbeLaserChip002", StatusReset(EnemyHisbeLaserChip002)) {
    _class_name = "EnemyHisbeLaserChip002";
    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pVecDriverLeader_ = pConn_pSplManuf_->peek()->createVecDriverLeader(callVecDriver());
    pVecDriverLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pFeatureScene_ = nullptr;
    callVecDriver()->setMvAngByFaceAng();
    callVecDriver()->linkFaceAngByMvAng(true);
}

void EnemyHisbeLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyHisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pFeatureScene_ = ((DefaultScene*)(getSceneMediator()->getPlatformScene()))->getNearestFeatureScene();
}

void EnemyHisbeLaserChip002::onRefractionInto(int prm_num_refraction)  {

}

void EnemyHisbeLaserChip002::onRefractionOutOf(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pVecDriverLeader_->start(RELATIVE_COORD_DIRECTION); //向てる方向にスプライン座標をワールド変換
    }
    pVecDriverLeader_->behave();
    if (pVecDriverLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::processBehavior() {
    if (_is_leader) {
        if (pFeatureScene_) {
            pVecDriverLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
        }
    }
    RefractionLaserChip::processBehavior();
}

void EnemyHisbeLaserChip002::processJudgement() {
    if (getActiveFrame() >= getRefractionFinishFrames()) {
        sayonara();
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyHisbeLaserChip002::~EnemyHisbeLaserChip002() {
    GGAF_DELETE(pVecDriverLeader_);
    pConn_pSplManuf_->close();
}


