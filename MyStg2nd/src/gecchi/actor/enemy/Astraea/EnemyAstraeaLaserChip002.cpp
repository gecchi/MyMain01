#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip002::EnemyAstraeaLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "AstraeaLaserChip001") {
    _class_name = "EnemyAstraeaLaserChip002";
    MyStgUtil::resetEnemyAstraeaLaserChip002Status(_pStatus);

}

void EnemyAstraeaLaserChip002::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleRate(5.0);
    setAlpha(0.9);
}

void EnemyAstraeaLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaLaserChip002Status(_pStatus);

    _pKurokoA->setMvVelo(80000);
    //_pKurokoA->setMvAcce(300);
    //_pKurokoA->forceRyMvAngVeloRange(-90000, 90000);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void EnemyAstraeaLaserChip002::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
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
        GgafDx9Util::getRzRyAng(P_MYSHIP->_X - _X,
                                P_MYSHIP->_Y - _Y,
                                P_MYSHIP->_Z - _Z,
                                out_angRz_Target,
                                out_angRy_Target);
        out_d_angRz = _pKurokoA->getRzMvAngDistance(out_angRz_Target, TURN_CLOSE_TO);
        out_d_angRy = _pKurokoA->getRyMvAngDistance(out_angRy_Target, TURN_CLOSE_TO);
        _pKurokoA->addRzMvAng(sgn(out_d_angRz)*20000);
        _pKurokoA->addRyMvAng(sgn(out_d_angRy)*30000);
//        _pKurokoA->execTurnMvAngSequence(
//                        P_MYSHIP,
//                        90000, 0,
//                        TURN_CLOSE_TO, false);

//        _pKurokoA->setMvAng(P_MYSHIP);
    }
}

void EnemyAstraeaLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //ヒットして消滅時
//        sayonara();
//    } else {
//        //ヒットして生存時
//    }
}

EnemyAstraeaLaserChip002::~EnemyAstraeaLaserChip002() {
}

