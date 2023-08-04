#include "EnemyStraightLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyStraightLaserChip001::EnemyStraightLaserChip001(const char* prm_name) :
        VvEnemyActor<StraightLaserChip>(prm_name, "EnemyStraightLaserChip001", StatusReset(EnemyStraightLaserChip001)) {
    _class_name = "EnemyStraightLaserChip001";
    setMvVelo(PX_C(200));
}

void EnemyStraightLaserChip001::initialize() {
    getLocoVehicle()->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(15000);
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);
}

void EnemyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    getStatus()->reset();
}

void EnemyStraightLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyStraightLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    if (getActiveFrame() <= 2 && (pOther->lookUpKind() & KIND_CHIKEI)) {
        //出現2フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    }
    bool is_stamina_zero = performEnemyHit(pOther);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyStraightLaserChip001::~EnemyStraightLaserChip001() {
}

