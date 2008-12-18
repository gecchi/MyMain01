#include "stdafx.h"

MyOption::MyOption(string prm_name,  string prm_model) : DefaultMeshActor(prm_name, prm_model) {
	_class_name = "MyOption";
	GeometryChain* pFirst = NEW GeometryChain(GameGlobal::_pMyShip);
	GeometryChain* pWork = pFirst;
	GeometryChain* pTemp = NULL;
	//for (DWORD i = 0; i < prm_dwBufferFrame-1; i++) {
	for (DWORD i = 0; i < 50-1; i++) {
		pTemp = NEW GeometryChain(GameGlobal::_pMyShip);
		pWork->_next = pTemp;
		pWork = pTemp;
	}
	pTemp->_next = pFirst;
	_pGeoChainRingActive = pFirst;


	_pMyLaserChipRotation = NEW RotationActor("RotLaser001");
	addSubLast(_pMyLaserChipRotation);//仮所属
	MyLaserChip* pChip;
	for (int i = 0; i < 30; i++) { //レーザーストック
		pChip = NEW MyLaserChip("MY_L"+GgafUtil::itos(i), "laserchip9");
		pChip->stopImmediately();
		_pMyLaserChipRotation->addSubLast(pChip);
	}

	_iMyNo = 0;

}

void MyOption::initialize() {
	getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaserChipRotation->tear());

	_pChecker -> useHitAreaBoxNum(1);
	_pChecker -> setHitAreaBox(0, -10000, -10000, 10000, 10000);
	if (_iMyNo == 0) {
		setGeometry(50000,0,0);
		_pGeoMover -> setMoveVelocity(3000);
		_pGeoMover -> setMoveAngleRz(5000);

	} else {
		_pGeoMover -> setMoveVelocity(0);
	}
	//_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	//_pGeoMover -> setAxisRotAngleVelocity(AXIS_Y,2000);
	//setAlpha(0.2);
}

void MyOption::processBehavior() {
	if (_iMyNo == 0) {
		//最初の
		_pGeoMover -> behave();
		_X += _pActor_Radical -> _X;
		_Y += _pActor_Radical -> _Y;
		_Z += _pActor_Radical -> _Z;


	} else {

		_X = _pGeoChainRingActive->_X;
		_Y = _pGeoChainRingActive->_Y;
		_Z = _pGeoChainRingActive->_Z;
		_pGeoChainRingActive->set(_pActor_Radical);
		_pGeoChainRingActive = _pGeoChainRingActive ->_next;

		//ショット関連処理
		//MyShip::transactShot(this);
		_pGeoMover -> behave();
	}
	//座標に反映

}



void MyOption::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}


void MyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


MyOption::~MyOption() {
	GeometryChain* pWork = _pGeoChainRingActive;
	GeometryChain* pWorkNext = NULL;
	for (DWORD i = 0; i < 50-1 + 1; i++) {
		pWorkNext = pWork->_next;
		DELETE_IMPOSSIBLE_NULL(pWork);
		pWork = pWorkNext;
	}

}
