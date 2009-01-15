#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

int FormationJuno001::_s_X_FormationWhole = 0;
int FormationJuno001::_s_incX = -2000;

FormationJuno001::FormationJuno001(string prm_name, string prm_model) : FormationActor(prm_name) {
	_class_name = "FormationJuno001";
	CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
	pRndGen->changeSeed(GameGlobal::_pMyShip->_X);

	int iScreenWidth = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT;
	int iScreenHeight = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT;
	for (int i = 0; i < NUM_JUNO_FORMATION001; i++) {
		_pEnemyJuno[i] = NEW EnemyJuno("Juno01", prm_model);
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
	if (isFirst()) {
		_s_X_FormationWhole += _s_incX; //‘S‘Ì‚ÌX
	}
}


FormationJuno001::~FormationJuno001() {
}
