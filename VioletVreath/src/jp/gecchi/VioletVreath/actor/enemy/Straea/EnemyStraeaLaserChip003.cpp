#include "EnemyStraeaLaserChip003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip003::EnemyStraeaLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "StraeaLaserChip001") {
    _class_name = "EnemyStraeaLaserChip003";
    getStatus()->reset(statusResetFunction(EnemyStraeaLaserChip003));
    pConn_pSplManuf_ = connectToSplineManufactureManager("GURUGURU");
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
}

void EnemyStraeaLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(30000);
    pKuroko->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pKurokoLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
}

void EnemyStraeaLaserChip003::processBehavior() {
    pKurokoLeader_->behave();
    getKuroko()->behave();
}

void EnemyStraeaLaserChip003::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyStraeaLaserChip003::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}
void EnemyStraeaLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyStraeaLaserChip003::~EnemyStraeaLaserChip003() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}

