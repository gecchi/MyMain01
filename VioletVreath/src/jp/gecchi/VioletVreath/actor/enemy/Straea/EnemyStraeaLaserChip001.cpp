#include "stdafx.h"
#include "EnemyStraeaLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip001::EnemyStraeaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "StraeaLaserChip001", STATUS(EnemyStraeaLaserChip001)) {
    _class_name = "EnemyStraeaLaserChip001";
}

void EnemyStraeaLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyStraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    _pKurokoA->setMvVelo(10000);
    _pKurokoA->setMvAcce(400);
    _pKurokoA->relateFaceWithMvAng(true);
}

void EnemyStraeaLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyStraeaLaserChip001::processBehaviorHeadChip() {
    if (getActiveFrame() == 40) {
        _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                7000, 0,
                                TURN_ANTICLOSE_TO, false);
    }


    if (!_pKurokoA->isTurningMvAng()) {
        _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                100, 0,
                                TURN_CLOSE_TO, false);
    }
//
//    if (frame_of_behaving_from_onActive_ == 35) {
//        _pKurokoA->turnMvAngTwd(
//                    P_MYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pKurokoA->behave();
}

void EnemyStraeaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

EnemyStraeaLaserChip001::~EnemyStraeaLaserChip001() {

}

