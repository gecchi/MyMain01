#include "stdafx.h"

EnemyMeshShot001::EnemyMeshShot001(string prm_name, string prm_model) : DefaultMeshEnemyActor(prm_name, prm_model) {
	declareStop();
}

void EnemyMeshShot001::initialize() {
	_pGeoMover -> setMoveVelocity(3000);
	_pGeoMover -> setMoveAcceleration(3000);
	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	setBumpableOnlySelf(true);
}



void EnemyMeshShot001::processBehavior() {
	if (switchedToPlay()) {
		//出現時
		setBumpableOnlySelf(true);
	}
	//nextAnimationFrame();
	//座標に反映
	_pGeoMover -> behave();

}

bool EnemyMeshShot001::isOffScreen() {
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

void EnemyMeshShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
	//_TRACE_("EnemyMeshShot001ヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	setBumpableOnlySelf(false);
	declareStop();
	EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
	if (pExplo001 != NULL) {
		pExplo001->setGeometry(this);
		pExplo001->declarePlay();
	}
}


EnemyMeshShot001::~EnemyMeshShot001() {
}
