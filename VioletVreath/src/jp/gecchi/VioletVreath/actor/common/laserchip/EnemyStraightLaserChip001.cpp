#include "EnemyStraightLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraightLaserChip001::EnemyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "EnemyStraightLaserChip001", STATUS(EnemyStraightLaserChip001)) {
    _class_name = "EnemyStraightLaserChip001";
    setMvVelo(PX_C(100));
}

void EnemyStraightLaserChip001::initialize() {
    getKuroko()->setRzRyMvAng(0,0);
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

void EnemyStraightLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() <= 2 && (pOther->lookUpKind() & KIND_CHIKEI)) {
        //出現2フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    }
    bool was_destroyed = UTIL::performEnemyHit(this, pOther);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyStraightLaserChip001::~EnemyStraightLaserChip001() {
}

