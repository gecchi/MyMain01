#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyShot001::EnemyShot001(const char* prm_name) : EnemyShotSpriteActor(prm_name, "hoge") {
    _class_name = "EnemyShot001";
    inactivateTree();
}

void EnemyShot001::initialize() {
    setAnimationMethod(ORDER_LOOP, 1);
    _pMover->setMoveVelocity(3000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    setBumpable(true);
}

void EnemyShot001::processBehavior() {
    if (onChangeToActive()) {
        //出現時
        setBumpable(true);
    }
    addNextAnimationFrame();
    //座標に反映
    _pMover->behave();

}

int EnemyShot001::isGone() {
    if (_X < _X_ScreenLeft) {
        return true;
    } else {
        if (_X > _X_ScreenRight) {
            return true;
        } else {
            if (_Y > _Y_ScreenTop) {
                return true;
            } else {
                if (_Y < _Y_ScreenBottom) {
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
    //adios();
    setBumpable(false);
    inactivateTree();
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activateTree();
    }
}

EnemyShot001::~EnemyShot001() {
}
