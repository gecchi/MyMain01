#include "stdafx.h"

EnemyMyShot001::EnemyMyShot001(string prm_name, string prm_xname) : EnemyShotSpriteActor(prm_name, prm_xname) {
	declareStop();
}

void EnemyMyShot001::initialize() {
	_iAnimationMethod = ORDER_LOOP;
	_iAnimationFrame_Interval = 1;

	_pMover -> setXYMoveVelocity(3000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -5000, -5000, 5000, 5000);

	setBumpable(true);
}



void EnemyMyShot001::processBehavior() {
	nextAnimationFrame();
	//座標に反映
	_pMover -> behave();

}

bool EnemyMyShot001::isOffScreen() {
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

void EnemyMyShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("EnemyMyShot001::processOnHit ショットがヒットしました");
	_TRACE_("EnemyMyShot001ヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();

	//体力計算
	if (_pChecker->_iStaminaPoint < 0) {
		declareStop();
	}


}

EnemyMyShot001::~EnemyMyShot001() {
}
