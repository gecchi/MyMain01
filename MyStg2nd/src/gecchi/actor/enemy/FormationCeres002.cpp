#include "stdafx.h"

FormationCeres002::FormationCeres002(string prm_name) : FormationActor(prm_name) {
	_class_name = "FormationCeres002";
	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		_pEnemyCeres[i] = NEW EnemyCeres("Ceres01", "ebi");
		_pEnemyCeres[i] -> stopImmediately();
		_pEnemyCeres[i] -> _Y_turn = (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2) - (i*40000);
		_pEnemyCeres[i] -> _iBeginVelocity = 10000;
		_pEnemyCeres[i] -> _Z = -4000000;
		addSubLast(_pEnemyCeres[i] );
	}
}

void FormationCeres002::initialize() {
	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		_pEnemyCeres[i] -> playAfter(i*20+1);
	}
}

FormationCeres002::~FormationCeres002() {
}
