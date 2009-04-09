#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyShot001::EnemyShot001(const char* prm_name) : EnemyShotSpriteActor(prm_name, "S/hoge") {
    _class_name = "EnemyShot001";
    inactivateTree();
}

void EnemyShot001::initialize() {
    setAnimationMethod(ORDER_LOOP, 1);
    _pGeoMover->setMoveVelocity(3000);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    setBumpableAlone(true);
}

void EnemyShot001::processBehavior() {
    if (switchedToActive()) {
        //出現時
        setBumpableAlone(true);
    }
    nextAnimationFrame();
    //座標に反映
    _pGeoMover->behave();

}

bool EnemyShot001::isOffScreen() {
    if (_X < _X_OffScreenLeft) {
        return true;
    } else {
        if (_X > _X_OffScreenRight) {
            return true;
        } else {
            if (_Y > _Y_OffScreenTop) {
                return true;
            } else {
                if (_Y < _Y_OffScreenBottom) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
}

void EnemyShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("EnemyShot001ヒットしました。("<<_X<<","<<_Y<<")");
    //arigatou_sayounara();
    setBumpableAlone(false);
    inactivateTree();
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activateTree();
    }
}

EnemyShot001::~EnemyShot001() {
}
