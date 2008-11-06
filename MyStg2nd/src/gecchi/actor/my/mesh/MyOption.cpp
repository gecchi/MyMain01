#include "stdafx.h"

MyOption::MyOption(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
}

void MyOption::initialize() {
	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pMover -> setMoveVelocity(0);
	//_pMover -> setAxisRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	//_pMover -> setAxisRotAngleVelocity(AXIS_Y,2000);
	_RZ = ANGLE90;
	//setAlpha(0.2);
}

void MyOption::processBehavior() {

	//À•W‚É”½‰f
	_pMover -> behave();
}



void MyOption::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}


void MyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


MyOption::~MyOption() {
}
