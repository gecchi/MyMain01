#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAdrastea001::FormationAdrastea001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationAdrastea001";
    for (int i = 0; i < NUM_METIS_FORMATION001; i++) {
        apEnemyAdrastea_[i] = NEW EnemyAdrastea("Adrastea01");
        apEnemyAdrastea_[i]->inactivateImmed();
        addSubLast(apEnemyAdrastea_[i] );
    }
}

void FormationAdrastea001::initialize() {
    for (int i = 0; i < NUM_METIS_FORMATION001; i++) {
        apEnemyAdrastea_[i]->activateDelay(i * 20 + 1);
    }
}

FormationAdrastea001::~FormationAdrastea001() {
}
