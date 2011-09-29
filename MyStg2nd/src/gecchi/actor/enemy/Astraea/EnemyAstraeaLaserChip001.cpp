
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


EnemyAstraeaLaserChip001::EnemyAstraeaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001", STATUS(EnemyAstraeaLaserChip001)) {
    _class_name = "EnemyAstraeaLaserChip001";
}

void EnemyAstraeaLaserChip001::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleRate(5.0);
    setAlpha(0.9);
}

void EnemyAstraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    _pKurokoA->setMvVelo(10000);
    _pKurokoA->setMvAcce(400);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void EnemyAstraeaLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyAstraeaLaserChip001::processBehaviorHeadChip() {
    if (getActivePartFrame() == 40) {
        _pKurokoA->execTurnMvAngSequence(
                    P_MYSHIP,
                    7000, 0,
                    TURN_ANTICLOSE_TO, false);
    }


    if (_pKurokoA->_mv_ang_ry_target_flg == false && _pKurokoA->_mv_ang_rz_target_flg == false) {
        _pKurokoA->execTurnMvAngSequence(
                    P_MYSHIP,
                    100, 0,
                    TURN_CLOSE_TO, false);
    }
//
//    if (_frame_of_behaving_from_onActive == 35) {
//        _pKurokoA->execTurnMvAngSequence(
//                    P_MYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pKurokoA->behave();
}

void EnemyAstraeaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

EnemyAstraeaLaserChip001::~EnemyAstraeaLaserChip001() {

}

