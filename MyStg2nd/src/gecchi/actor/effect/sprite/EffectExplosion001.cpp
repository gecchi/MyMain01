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
	nextAnimationFrame();
	_SX += 3000;
	_SY += 3000;
	//座標に反映
	_pMover -> behave();
}

void EffectExplosion001::processJudgement() {
	if (_iAnimationPatternNo_Active >= _iAnimationPatternNo_Bottom) {
		declareStop();
	}
}

//オーバーライド
void EffectExplosion001::happen(int prm_event) {
	//共通呼び出し
	DefaultSpriteActor::happen(prm_event);

	switch (prm_event) {
	case GGAF_EVENT_PLAY_BEGIN:
		//出現時共通処理
		_iAnimationPatternNo_Active = 0;
		_X = GameGlobal::_pMyShip->_X;
		_Y = GameGlobal::_pMyShip->_Y;
		_Z = GameGlobal::_pMyShip->_Z;
		break;
	default:
		break;
	}
}

void EffectExplosion001::processOnHit(GgafActor* prm_pActor_Opponent) {
}

EffectExplosion001::~EffectExplosion001() {
}
