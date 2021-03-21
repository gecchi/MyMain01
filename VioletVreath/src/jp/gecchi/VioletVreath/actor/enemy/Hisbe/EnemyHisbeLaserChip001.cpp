#include "EnemyHisbeLaserChip001.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip001::EnemyHisbeLaserChip001(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "HisbeLaserChip001", StatusReset(EnemyHisbeLaserChip001)) {
    _class_name = "EnemyHisbeLaserChip001";
    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pRikishaLeader_ = pConn_pSplManuf_->peek()->createRikishaLeader(callRikisha());
    pScrollingScene_ = nullptr;
    callRikisha()->setMvAngByFaceAng();
    callRikisha()->linkFaceAngByMvAng(true);
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
    registerpScrollingSplineLeader(pRikishaLeader_);
}

void EnemyHisbeLaserChip001::onInactive() {
    HomingLaserChip::onInactive();
    pRikishaLeader_->stop();
}

void EnemyHisbeLaserChip001::processBehaviorHeadChip() {
    if (getActiveFrame() == 1) {
        return;
    }

    if (getActiveFrame() == 2) {
        pRikishaLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
    }
    pRikishaLeader_->behave();
    callRikisha()->behave();
    if (pRikishaLeader_->isFinished()) {
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
    GGAF_DELETE(pRikishaLeader_);
    pConn_pSplManuf_->close();
}

