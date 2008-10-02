#include "stdafx.h"

Explosion001Actor::Explosion001Actor(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {
}

void Explosion001Actor::initialize() {
	_canBump  = false;
	_iAnimationMethod = EVENT_REVERSE_NOLOOP_ANIMATION_FINISH;
	_iAnimationPatternNo_Active = 0;
	_iAnimationPatternNo_Top = 0;
	_iAnimationPatternNo_Bottom = 15;
}

void Explosion001Actor::processBehavior() {
	addAnimationFrame();
	_SX += 3000;
	_SY += 3000;
	//���W�ɔ��f
	_pMover -> behave();
}

void Explosion001Actor::processJudgement() {
	if (_iAnimationPatternNo_Active >= _iAnimationPatternNo_Bottom) {
		declareStop();
	}
}

//�I�[�o�[���C�h
void Explosion001Actor::happen(int prm_event) {
	//���ʌĂяo��
	DefaultSpriteActor::happen(prm_event);

	switch (prm_event) {
	case EVENT_PLAY_BEGIN:
		//�o�������ʏ���
		_iAnimationPatternNo_Active = 0;
		_X = GameGlobal::_pMyShipActor->_X;
		_Y = GameGlobal::_pMyShipActor->_Y;
		_Z = GameGlobal::_pMyShipActor->_Z;
		break;
	default:
		break;
	}
}

void Explosion001Actor::processOnHit(GgafActor* prm_pActor_Opponent) {
}

Explosion001Actor::~Explosion001Actor() {
}
