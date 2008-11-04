#include "stdafx.h"

MyLaser001* MyLaser001::_pHeadMyLaser001 = NULL;

MyLaser001::MyLaser001(string prm_name, string prm_xname) : DefaultSpriteMyActor(prm_name, prm_xname) {
	_X_prevFrame = 0;
}

void MyLaser001::initialize() {
	setAnimationMethod(ORDER_LOOP, 1);

	_pMover -> setMoveAngleRzVelocity(0);
	_pMover -> setMoveAngleRz(0);
	_pMover -> setMoveVelocity(_pSpriteModel->_fSize_SpriteModelWidthPx * 1000);

	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -5000, -5000, 5000, 5000);

	setBumpableOnlySelf(true);
}


void MyLaser001::processBehavior() {
	if (switchedToPlay()) {
		//�o��������
		setBumpableOnlySelf(true);
		_X = GameGlobal::_pMyShip->_X;
		_X_prevFrame = _X;
		_Y = GameGlobal::_pMyShip->_Y;
		_Z = GameGlobal::_pMyShip->_Z;
	} else {
		//�ʏ폈��
		nextAnimationFrame();
		//���W�ɔ��f
		_pMover -> behave();
		_Y = GameGlobal::_pMyShip->_Y;
	}
}

void MyLaser001::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		declareStop();
	}
}

/*
bool MyLaser001::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("MyLaser001::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"��"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void MyLaser001::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("MyLaser001::processOnHit �V���b�g���q�b�g���܂���");
	_TRACE_("MyLaser001�q�b�g���܂����B("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	declareStop();
}

void MyLaser001::onStop() {
	setBumpableOnlySelf(false);
	if (MyLaser001::_pHeadMyLaser001 == this) {
		MyLaser001::_pHeadMyLaser001 = NULL;
	}
}

MyLaser001::~MyLaser001() {

}
