#include "stdafx.h"

FormationCeres001::FormationCeres001(string prm_name) : FormationActor(prm_name) {
	_class_name = "FormationCeres001";
	for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
		_pEnemyCeres[i] = NEW EnemyCeres("Ceres01", "Ceres");
		_pEnemyCeres[i] -> stopImmediately();
		addSubLast(_pEnemyCeres[i] );
	}
}

void FormationCeres001::initialize() {
	for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
		_pEnemyCeres[i] -> playAfter(i*30+1);
	}
}

FormationCeres001::~FormationCeres001() {
}
