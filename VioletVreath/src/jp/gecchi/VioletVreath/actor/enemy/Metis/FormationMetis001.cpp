#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationMetis001::FormationMetis001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationMetis001";
    for (int i = 0; i < NUM_METIS_FORMATION001; i++) {
        apEnemyMetis_[i] = NEW EnemyMetis("Metis01");
        apEnemyMetis_[i]->inactivateImmed();
        addSubLast(apEnemyMetis_[i] );
    }
}

void FormationMetis001::initialize() {
    for (int i = 0; i < NUM_METIS_FORMATION001; i++) {
        apEnemyMetis_[i]->activateDelay(i * 20 + 1);
    }
}

FormationMetis001::~FormationMetis001() {
}
