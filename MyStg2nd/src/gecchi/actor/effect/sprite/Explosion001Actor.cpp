#include "stdafx.h"

Explosion001Actor::Explosion001Actor(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {
}

void Explosion001Actor::initialize() {
	_canBump  = false;
	_iAnimationMethod = ORDER_LOOP;
	_iAnimationPatternNo_Active = 0;
}

void Explosion001Actor::processBehavior() {
	addAnimationFrame();
	_SX += 3000;
	_SY += 3000;
	//À•W‚É”½‰f
	_pMover -> behave();
}

void Explosion001Actor::processJudgement() {
	if (_iAnimationPatternNo_Active >= _iAnimationPatternNo_Bottom) {
		declareStop();
	}
}


void Explosion001Actor::processOnHit(GgafActor* prm_pActor_Opponent) {
}

Explosion001Actor::~Explosion001Actor() {
}
