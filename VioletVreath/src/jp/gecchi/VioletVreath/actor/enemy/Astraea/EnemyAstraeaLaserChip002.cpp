#include "stdafx.h"
#include "EnemyAstraeaLaserChip002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAstraeaLaserChip002::EnemyAstraeaLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "AstraeaLaserChip001", STATUS(EnemyAstraeaLaserChip002)) {
    _class_name = "EnemyAstraeaLaserChip002";
    pConne_RefractionEffectDepository_ = nullptr;
}

void EnemyAstraeaLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyAstraeaLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    _pKurokoA->setMvVelo(80000);
    //_pKurokoA->setMvAcce(300);
    //_pKurokoA->forceRyMvAngVeloRange(-90000, 90000);
    _pKurokoA->relateMvFaceAng(true);
}

void EnemyAstraeaLaserChip002::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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


void EnemyAstraeaLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyAstraeaLaserChip002::onRefractionFinish(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {

    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        angle out_d_angRz;
        angle out_d_angRy;
        UTIL::convVectorToRzRy(P_MYSHIP->_X - _X,
                               P_MYSHIP->_Y - _Y,
                               P_MYSHIP->_Z - _Z,
                               out_angRz_Target,
                               out_angRy_Target);
        out_d_angRz = _pKurokoA->getRzMvAngDistance(out_angRz_Target, TURN_CLOSE_TO);
        out_d_angRy = _pKurokoA->getRyMvAngDistance(out_angRy_Target, TURN_CLOSE_TO);
        _pKurokoA->addRzMvAng(SGN(out_d_angRz)*20000);
        _pKurokoA->addRyMvAng(SGN(out_d_angRy)*30000);
//        _pKurokoA->turnMvAngTwd(
//                        P_MYSHIP,
//                        90000, 0,
//                        TURN_CLOSE_TO, false);

//        _pKurokoA->setMvAngTwd(P_MYSHIP);
    }
}

void EnemyAstraeaLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        //ヒットして消滅時
//        sayonara();
//    } else {
//        //ヒットして生存時
//    }
}

EnemyAstraeaLaserChip002::~EnemyAstraeaLaserChip002() {
}

