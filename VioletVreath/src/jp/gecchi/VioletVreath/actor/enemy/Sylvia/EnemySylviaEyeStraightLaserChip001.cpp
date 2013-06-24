#include "stdafx.h"
#include "EnemySylviaEyeStraightLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemySylviaEyeStraightLaserChip001::EnemySylviaEyeStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "SylviaEyeStraightLaserChip001", STATUS(EnemySylviaEyeStraightLaserChip001)) {
    _class_name = "EnemySylviaEyeStraightLaserChip001";
    _veloMv = 500000;
}

void EnemySylviaEyeStraightLaserChip001::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(300000);
    setHitAble(true, false); //画面外当たり判定は無し
    //setScaleR(5.0);
    setScaleR(500.0);
    setAlpha(0.9);
}

void EnemySylviaEyeStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pKurokoA->setMvVelo(100000);
    _pKurokoA->setMvAcce(300);
    _pStatus->reset();
}

void EnemySylviaEyeStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemySylviaEyeStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    //playSe3D1();
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        //sayonara();
    }

}


EnemySylviaEyeStraightLaserChip001::~EnemySylviaEyeStraightLaserChip001() {
}

