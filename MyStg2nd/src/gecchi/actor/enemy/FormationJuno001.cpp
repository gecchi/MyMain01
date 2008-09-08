#include "stdafx.h"

FormationJuno001::FormationJuno001(string prm_name) : FormationActor(prm_name) {
	_class_name = "FormationJuno001";
	for (int i = 0; i < NUM_JUNO_FORMATION001; i++) {
		_pEnemyJuno[i] = NEW EnemyJuno("Juno01", "ebi");
		_pEnemyJuno[i] -> stopImmediately();
		addSubLast(_pEnemyJuno[i] );
	}
}

void FormationJuno001::initialize() {
	for (int i = 0; i < NUM_JUNO_FORMATION001; i++) {
		_pEnemyJuno[i] -> playAfter(i*30+1);
	}
}

FormationJuno001::~FormationJuno001() {
}
