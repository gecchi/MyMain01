#include "stdafx.h"

FormationVesta001::FormationVesta001(string prm_name) : FormationActor(prm_name) {
	_class_name = "FormationVesta001";
	for (int i = 0; i < NUM_VESTA_FORMATION001; i++) {
		_pEnemyVesta[i] = NEW EnemyVesta("Vesta01", "ebi");
		_pEnemyVesta[i] -> stopImmediately();
		addSubLast(_pEnemyVesta[i] );
	}
}

void FormationVesta001::initialize() {
	for (int i = 0; i < NUM_VESTA_FORMATION001; i++) {
		_pEnemyVesta[i] -> playAfter(i*30+1);
	}
}

FormationVesta001::~FormationVesta001() {
}
