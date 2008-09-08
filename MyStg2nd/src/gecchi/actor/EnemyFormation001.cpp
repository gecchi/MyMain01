#include "stdafx.h"

EnemyFormation001::EnemyFormation001(string prm_name) : FormationActor(prm_name) {
	_class_name = "EnemyFormation001";
	for (int i = 0; i < NUM_FORMATION001; i++) {
		_pEnemyCeres[i] = NEW EnemyCeres("Ceres01", "ebi");
		_pEnemyCeres[i] -> stopImmediately();
		addSubLast(_pEnemyCeres[i] );
	}
}

void EnemyFormation001::initialize() {
	for (int i = 0; i < NUM_FORMATION001; i++) {
		_pEnemyCeres[i] -> playAfter(i*5+1);
	}
}

EnemyFormation001::~EnemyFormation001() {
}
