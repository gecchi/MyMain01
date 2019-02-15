#include "EnemyEmusLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;


EnemyEmusLaserChip001::EnemyEmusLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "EmusLaserChip001") {
    _class_name = "EnemyEmusLaserChip001";
    getStatus()->reset(statusResetFunction(EnemyEmusLaserChip001));
}

void EnemyEmusLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(300000);
    pKuroko->linkFaceAngByMvAng(true);
}

void EnemyEmusLaserChip001::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
}

void EnemyEmusLaserChip001::processBehavior() {
    getKuroko()->behave();
}

void EnemyEmusLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEmusLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    if (getActiveFrame() < 30 && (pOther->lookUpKind() & KIND_CHIKEI)) {
        //出現30フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    } else {
        bool was_destroyed = UTIL::performEnemyHit(this, pOther);
        if (was_destroyed) {
            //破壊された時(スタミナ <= 0)
            sayonara();
        } else {
            //破壊されなかった時(スタミナ > 0)
        }
    }
}
void EnemyEmusLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyEmusLaserChip001::~EnemyEmusLaserChip001() {
}

