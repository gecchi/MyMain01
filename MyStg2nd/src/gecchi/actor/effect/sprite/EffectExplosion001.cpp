#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectExplosion001::EffectExplosion001(const char* prm_name) : DefaultSpriteActor(prm_name, "S/EffectExplosion001") {
    _class_name = "EffectExplosion001";
}

void EffectExplosion001::initialize() {
    setAnimationMethod(ORDER_NOLOOP, 1);
    setAnimationPatternRenge(0, 15);
    setBumpable(false);

    _SX = _SY = _SZ = 10*1000;

}

void EffectExplosion001::processBehavior() {
    if (onChangeToActive()) {
        //oŒ»Žžˆ—
        setActivAnimationPattern(0);
        _fAlpha = 0.99;
        _SX = _SY = _SZ = 10*1000;
        //		_X = GameGlobal::_pMyShip->_X;
        //		_Y = GameGlobal::_pMyShip->_Y;
        //		_Z = GameGlobal::_pMyShip->_Z;
    } else {

        _fAlpha -= 0.03;
        _SX+= 100;
        _SY+= 100;
        addNextAnimationFrame();
        //		_SX += 3000;
        //		_SY += 3000;
        //À•W‚É”½‰f
        _pGeoMover->behave();
    }
}

void EffectExplosion001::processJudgement() {
    if (_pattno_ani_now >= _pattno_ani_bottom) {
        inactivateAfter(60);
    }
}

EffectExplosion001::~EffectExplosion001() {
}
