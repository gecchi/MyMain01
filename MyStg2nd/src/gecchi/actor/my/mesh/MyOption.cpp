#include "stdafx.h"

MyOption::MyOption(DWORD prm_dwBufferFrame,  string prm_model) : DefaultMeshActor("OPTION", prm_model) {
	GeometryChain* pFirst = NEW GeometryChain(this);
	GeometryChain* pWork = pFirst;
	GeometryChain* pTemp = pFirst;
	for (DWORD i = 0; i < prm_dwBufferFrame-1; i++) {
		pTemp = NEW GeometryChain(this);
		pWork->_next = pTemp;
		pWork = pTemp;
	}
	pTemp->_next = pWork;
	_pGeoChainRingActive = pFirst;
}

void MyOption::initialize() {
	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pGeoMover -> setMoveVelocity(0);
	//_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	//_pGeoMover -> setAxisRotAngleVelocity(AXIS_Y,2000);
	//setAlpha(0.2);
}

void MyOption::processBehavior() {
	_X = _pGeoChainRingActive->_X;
	_Y = _pGeoChainRingActive->_Y;
	_Z = _pGeoChainRingActive->_Z;
	_pGeoChainRingActive->set(GameGlobal::_pMyShip);
	_pGeoChainRingActive = _pGeoChainRingActive ->_next;

	//ショット関連処理
	MyShip::transactShot(this);

	//座標に反映
	_pGeoMover -> behave();
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
	while (true) {
		pWorkNext = pWork->_next;
		DELETE_IMPOSSIBLE_NULL(pWork);
		pWork = NULL;
		if (pWorkNext != NULL) {
			pWork = pWorkNext;
		} else {
			break;
		}
	}

}
