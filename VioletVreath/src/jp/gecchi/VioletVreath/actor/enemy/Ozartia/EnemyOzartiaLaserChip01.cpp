#include "stdafx.h"
#include "EnemyOzartiaLaserChip01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartiaLaserChip01::EnemyOzartiaLaserChip01(const char* prm_name) :
        StraightLaserChip(prm_name, "EnemyOzartiaLaserChip01", STATUS(EnemyOzartiaLaserChip01)) {
    _class_name = "EnemyOzartiaLaserChip01";
    _veloMv = 100000;
}

void EnemyOzartiaLaserChip01::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false); //‰æ–ÊŠO“–‚½‚è”»’è‚Í–³‚µ
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyOzartiaLaserChip01::onActive() {
    StraightLaserChip::onActive();
    _pKurokoA->setMvVelo(100000);
    _pKurokoA->setMvAcce(300);
    _pStatus->reset();
}

void EnemyOzartiaLaserChip01::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void EnemyOzartiaLaserChip01::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        sayonara();
    }
}

EnemyOzartiaLaserChip01::~EnemyOzartiaLaserChip01() {
}

