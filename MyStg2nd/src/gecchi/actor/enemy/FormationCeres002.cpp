#include "stdafx.h"

FormationCeres002::FormationCeres002(string prm_name, string prm_model) : FormationActor(prm_name) {
	_class_name = "FormationCeres002";
	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		_pEnemyCeres[i] = NEW EnemyCeres("Ceres01", prm_model);
		_pEnemyCeres[i] -> stopImmediately();
		_pEnemyCeres[i] -> _Y_turn = -1*(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2) + (i * ((GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT)/NUM_CERES_FORMATION002)) ;
		_pEnemyCeres[i] -> _iBeginVelocity = 5000;
		_pEnemyCeres[i] -> _Z = -1500000;
		addSubLast(_pEnemyCeres[i] );
	}
}

void FormationCeres002::initialize() {
	for (int i = 0; i < NUM_CERES_FORMATION002; i++) {
		_pEnemyCeres[i] -> playAfter(i*80+1);
	}
}

FormationCeres002::~FormationCeres002() {
}
