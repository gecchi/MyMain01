#include "stdafx.h"

MyLaser001* MyLaser001::_pHeadMyLaser001 = NULL;

MyLaser001::MyLaser001(string prm_name, string prm_xname) : DefaultSpriteMyActor(prm_name, prm_xname) {
	_X_prevFrame = 0;
}

void MyLaser001::initialize() {
	_iAnimationMethod = ORDER_LOOP;
	_iAnimationFrame_Interval = 3;

	_pMover -> setXYMoveAngleVelocity(0);
	_pMover -> setXYMoveAngle(0);
	_pMover -> setXYMoveVelocity(_pSpriteModel->_fSize_SpriteModelWidthPx * 1000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -5000, -5000, 5000, 5000);

	setBumpable(false);
}
//�I�[�o�[���C�h
void MyLaser001::happen(int prm_event) {
	switch (prm_event) {

	case GGAF_EVENT_PLAY_BEGIN:
		//�o�������ʏ���
		setBumpable(true);
		_X = GameGlobal::_pMyShip->_X;
		_X_prevFrame = _X;
		_Y = GameGlobal::_pMyShip->_Y;
		_Z = GameGlobal::_pMyShip->_Z;
		break;

	case GGAF_EVENT_STOP_BEGIN:
		//���������ʏ���
		setBumpable(false);
		if (MyLaser001::_pHeadMyLaser001 == this) {
			MyLaser001::_pHeadMyLaser001 = NULL;
		}
		declareMoveFirst();
		break;

	default:
		break;
	}
}

void MyLaser001::processBehavior() {
	nextAnimationFrame();
	//���W�ɔ��f
	_pMover -> behave();

	_Y = GameGlobal::_pMyShip->_Y;
//	_X -= (_X_prevFrame - GameGlobal::_pMyShip->_X);
//	_X_prevFrame = _X;
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



MyLaser001::~MyLaser001() {
}
