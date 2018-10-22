#include "EnemyHisbeLaserChip002.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHisbeLaserChip002::EnemyHisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "HisbeLaserChip002", STATUS(EnemyHisbeLaserChip002)) {
    _class_name = "EnemyHisbeLaserChip002";
    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
    pKurokoLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pScrollingScene_ = nullptr;
    getKuroko()->setMvAngByFaceAng();
    getKuroko()->linkFaceAngByMvAng(true);
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
    pScrollingScene_ = ((DefaultScene*)(getMySceneMediator()->getPlatformScene()))->getNearestScrollingScene();
}

void EnemyHisbeLaserChip002::onRefractionInto(int prm_num_refraction)  {

}

void EnemyHisbeLaserChip002::onRefractionOutOf(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pKurokoLeader_->start(RELATIVE_COORD_DIRECTION); //向てる方向にスプライン座標をワールド変換
    }
    pKurokoLeader_->behave();
    if (pKurokoLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::processBehavior() {
    if (_is_leader) {
        if (pScrollingScene_) {
            pKurokoLeader_->_x_start_in_loop -= pScrollingScene_->getScrollSpeed();
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

void EnemyHisbeLaserChip002::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyHisbeLaserChip002::~EnemyHisbeLaserChip002() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}


