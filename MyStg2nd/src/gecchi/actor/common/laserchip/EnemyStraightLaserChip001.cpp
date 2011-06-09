#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyStraightLaserChip001::EnemyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "EnemyStraightLaserChip001") {
    _class_name = "EnemyStraightLaserChip001";
    MyStgUtil::resetEnemyStraightLaserChip001Status(_pStatus);
    _veloMv = 100000;
}

void EnemyStraightLaserChip001::initialize() {
    _pMvNavigator->setRzRyMvAng(0,0);
    registHitAreaCube(20000);
    setHitAble(true, false); //画面外当たり判定は無し
    setScaleRate(5.0);
    setAlpha(0.9);
}

void EnemyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pMvNavigator->setMvVelo(100000);
    _pMvNavigator->setMvAcce(300);
    MyStgUtil::resetEnemyStraightLaserChip001Status(_pStatus);
}

void EnemyStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    //playSe3D1();
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        sayonara();
    }

}


EnemyStraightLaserChip001::~EnemyStraightLaserChip001() {
}

