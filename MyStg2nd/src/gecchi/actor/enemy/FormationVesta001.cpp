#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationVesta001::FormationVesta001(const char* prm_name, const char* prm_model) : FormationActor(prm_name) {
	_class_name = "FormationVesta001";
	for (int i = 0; i < NUM_VESTA_FORMATION001; i++) {
		_pEnemyVesta[i] = NEW EnemyVesta("Vesta01", prm_model);
		_pEnemyVesta[i]->refrainImmediatelyAlone();
		addSubLast(_pEnemyVesta[i] );
	}
}

void FormationVesta001::initialize() {
	for (int i = 0; i < NUM_VESTA_FORMATION001; i++) {
		_pEnemyVesta[i]->actAfter(i*30+1);
	}
}

FormationVesta001::~FormationVesta001() {
}
