#include "EnemyHisbeLaserChip001.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip001::EnemyHisbeLaserChip001(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "HisbeLaserChip001", StatusReset(EnemyHisbeLaserChip001)) {
    _class_name = "EnemyHisbeLaserChip001";
    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pVecDriverLeader_ = pConn_pSplManuf_->peek()->createVecDriverLeader(callVecDriver());
    pFeatureScene_ = nullptr;
    callVecDriver()->setMvAngByFaceAng();
    callVecDriver()->linkFaceAngByMvAng(true);
}

void EnemyHisbeLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyHisbeLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    registerpFeatureSplineLeader(pVecDriverLeader_);
}

void EnemyHisbeLaserChip001::onInactive() {
    HomingLaserChip::onInactive();
    pVecDriverLeader_->stop();
}

void EnemyHisbeLaserChip001::processBehaviorHeadChip() {
    if (getActiveFrame() == 1) {
        return;
    }

    if (getActiveFrame() == 2) {
        pVecDriverLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
    }
    pVecDriverLeader_->behave();
    callVecDriver()->behave();
    if (pVecDriverLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyHisbeLaserChip001::~EnemyHisbeLaserChip001() {
    GGAF_DELETE(pVecDriverLeader_);
    pConn_pSplManuf_->close();
}

