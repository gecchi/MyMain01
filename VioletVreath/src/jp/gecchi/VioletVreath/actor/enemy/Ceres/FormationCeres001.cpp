#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationCeres001::FormationCeres001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationCeres001";
    for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
        _pEnemyCeres[i] = NEW EnemyCeres("Ceres01");
        _pEnemyCeres[i]->inactivateImmed();
        addSubLast(_pEnemyCeres[i] );
    }
}

void FormationCeres001::initialize() {
    for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
        _pEnemyCeres[i]->activateDelay(i * 30 + 1);
    }
}

FormationCeres001::~FormationCeres001() {
}
