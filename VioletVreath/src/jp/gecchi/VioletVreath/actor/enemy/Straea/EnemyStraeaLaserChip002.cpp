#include "stdafx.h"
#include "EnemyStraeaLaserChip002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip002::EnemyStraeaLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "StraeaLaserChip001", STATUS(EnemyStraeaLaserChip002)) {
    _class_name = "EnemyStraeaLaserChip002";
    pConn_RefractionEffectDepository_ = nullptr;
}

void EnemyStraeaLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyStraeaLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(80000);
    //_pKuroko->setMvAcce(300);
    //_pKuroko->forceRyMvAngVeloRange(-90000, 90000);
    pKuroko->relateFaceWithMvAng(true);
}

void EnemyStraeaLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyStraeaLaserChip002::onRefractionFinish(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {

    } else {
        GgafDxKuroko* pKuroko = getKuroko();
        angle out_angRz_Target;
        angle out_angRy_Target;
        angle out_d_angRz;
        angle out_d_angRy;
        UTIL::convVectorToRzRy(P_MYSHIP->_x - _x,
                               P_MYSHIP->_y - _y,
                               P_MYSHIP->_z - _z,
                               out_angRz_Target,
                               out_angRy_Target);
        out_d_angRz = pKuroko->getRzMvAngDistance(out_angRz_Target, TURN_CLOSE_TO);
        out_d_angRy = pKuroko->getRyMvAngDistance(out_angRy_Target, TURN_CLOSE_TO);
        pKuroko->addRzMvAng(SGN(out_d_angRz)*20000);
        pKuroko->addRyMvAng(SGN(out_d_angRy)*30000);
//        pKuroko->turnMvAngTwd(
//                        P_MYSHIP,
//                        90000, 0,
//                        TURN_CLOSE_TO, false);

//        pKuroko->setMvAngTwd(P_MYSHIP);
    }
}

void EnemyStraeaLaserChip002::onHit(GgafActor* prm_pOtherActor) {
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

EnemyStraeaLaserChip002::~EnemyStraeaLaserChip002() {
}

