#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationCeres001::FormationCeres001(const char* prm_name) : FormationActor(prm_name) {
    _class_name = "FormationCeres001";
    for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
        _pEnemyCeres[i] = NEW EnemyCeres("Ceres01");
        _pEnemyCeres[i]->inactivateImmediately();
        addSubLast(_pEnemyCeres[i] );
    }
}

void FormationCeres001::initialize() {
    for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
        _pEnemyCeres[i]->activateAfter(i * 30 + 1);
    }
}

FormationCeres001::~FormationCeres001() {
}
