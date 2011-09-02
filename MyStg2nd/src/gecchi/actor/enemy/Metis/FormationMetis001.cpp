#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationMetis001::FormationMetis001(const char* prm_name) : FormationActor(prm_name) {
    _class_name = "FormationMetis001";
    for (int i = 0; i < NUM_METIS_FORMATION001; i++) {
        _pEnemyMetis[i] = NEW EnemyMetis("Metis01");
        _pEnemyMetis[i]->inactivateImmediately();
        addSubLast(_pEnemyMetis[i] );
    }
}

void FormationMetis001::initialize() {
    for (int i = 0; i < NUM_METIS_FORMATION001; i++) {
        _pEnemyMetis[i]->activateDelay(i * 20 + 1);
    }
}

FormationMetis001::~FormationMetis001() {
}
