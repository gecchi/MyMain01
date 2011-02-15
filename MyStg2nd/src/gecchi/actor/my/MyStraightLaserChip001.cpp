#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyCurveLaserChip001") {
    _class_name = "MyStraightLaserChip001";
    MyStgUtil::resetMyStraightLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _veloMv = 100000;
}

void MyStraightLaserChip001::initialize() {
    _pMover->setRzRyMvAng(0,0);
    registHitAreaCube(60000);
    setHitAble(true);
    _SX = _SY = _SZ = 5 * 1000;
    _fAlpha = 0.99;
    _fBoundingSphereRadius = 20.0;
}

void MyStraightLaserChip001::processBehavior() {
    StraightLaserChip::processBehavior();
    //根元からレーザー表示のため強敵に座標補正
    if (onChangeToActive()) {
        setCoordinateBy(P_MYSHIP);
    }
}



void MyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pMover->setMvVelo(80000);
    _pMover->setMvAcce(300);
    MyStgUtil::resetMyStraightLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
}

void MyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;


    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力

            //破壊されたエフェクト
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
            if (pExplo001) {
                pExplo001->setCoordinateBy(this);
                pExplo001->activate();
            }
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            _pStatus->set(STAT_Stamina, _default_stamina);
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        //破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        if (pExplo001) {
            pExplo001->setCoordinateBy(this);
            pExplo001->activate();
        }
        sayonara();
    }

}


MyStraightLaserChip001::~MyStraightLaserChip001() {
}

