#include "stdafx.h"

int FormationJuno001::_X_whole = 0;
int FormationJuno001::_incX_whole = -500;

FormationJuno001::FormationJuno001(string prm_name) : FormationActor(prm_name) {
	_class_name = "FormationJuno001";
	CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
	pRndGen->changeSeed(GameGlobal::_pMyShipActor->_X);

	int iScreenWidth = GGAFDX9_PROPERTY(SCREEN_WIDTH)*LEN_UNIT;
	int iScreenHeight = GGAFDX9_PROPERTY(SCREEN_HEIGHT)*LEN_UNIT;
	for (int i = 0; i < NUM_JUNO_FORMATION001; i++) {
		_pEnemyJuno[i] = NEW EnemyJuno("Juno01", "ebi");
		_pEnemyJuno[i] -> stopImmediately();
		_pEnemyJuno[i]->_X = (pRndGen->genrand_int32() % (iScreenWidth)) - (iScreenHeight/2);
		_pEnemyJuno[i]->_Y = (pRndGen->genrand_int32() % (iScreenHeight)) - (iScreenHeight/2);
		addSubLast(_pEnemyJuno[i] );
		Sleep(1);
	}

}



void FormationJuno001::initialize() {
	for (int i = 0; i < NUM_JUNO_FORMATION001; i++) {
		_pEnemyJuno[i] -> playAfter(i*3+1);
	}
}

void FormationJuno001::processBehavior() {
	_X_whole += _incX_whole; //‘S‘Ì‚ÌX
}


FormationJuno001::~FormationJuno001() {
}
