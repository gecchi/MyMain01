#include "stdafx.h"

EffectExplosion001::EffectExplosion001(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {
}

void EffectExplosion001::initialize() {
	_canBump  = false;
	_iAnimationMethod = ORDER_NOLOOP;
	_iAnimationPatternNo_Active = 0;
	_iAnimationPatternNo_Top = 0;
	_iAnimationPatternNo_Bottom = 15;
}

void EffectExplosion001::processBehavior() {
	if (switchedToPlay()) {
		//oŒ»Žžˆ—
		_iAnimationPatternNo_Active = 0;
		_X = GameGlobal::_pMyShip->_X;
		_Y = GameGlobal::_pMyShip->_Y;
		_Z = GameGlobal::_pMyShip->_Z;
	} else {
		//•’Ê‚Ìˆ—
		nextAnimationFrame();
		_SX += 3000;
		_SY += 3000;
		//À•W‚É”½‰f
		_pMover -> behave();
	}
}

void EffectExplosion001::processJudgement() {
	if (_iAnimationPatternNo_Active >= _iAnimationPatternNo_Bottom) {
		declareStop();
	}
}


EffectExplosion001::~EffectExplosion001() {
}
