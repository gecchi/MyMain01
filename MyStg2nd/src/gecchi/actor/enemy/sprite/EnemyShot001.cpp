#include "stdafx.h"

EnemyShot001::EnemyShot001(string prm_name, string prm_xname) : EnemyShotSpriteActor(prm_name, prm_xname) {
	declareStop();
}

void EnemyShot001::initialize() {
	setAnimationMethod(ORDER_LOOP, 1);
	_pMover -> setXYMoveVelocity(3000);
	_pChecker -> _pHitAreaBoxs = NEW HitAreaBoxs(1);
	_pChecker -> _pHitAreaBoxs -> setBox(0, -10000, -10000, 10000, 10000);
	setBumpableOnlySelf(true);
}



void EnemyShot001::processBehavior() {
	nextAnimationFrame();
	//座標に反映
	_pMover -> behave();

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
//_TRACE_("EnemyShot001::processOnHit ショットがヒットしました");
	_TRACE_("EnemyShot001ヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	setBumpableOnlySelf(false);
	declareFinishLife();
	EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
	if (pExplo001) {
		pExplo001->setGeometry(this);
		pExplo001->declarePlay();
	}
}


EnemyShot001::~EnemyShot001() {
}
