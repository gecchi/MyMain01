#include "FormationEtis001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Etis/EnemyEtis.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationEtis001::FormationEtis001(const char* prm_name) : VvFormationActor<TreeFormation>(prm_name) {
    _class_name = "FormationEtis001";
    for (int i = 0; i < NUM_ETIS_FORMATION001; i++) {
        apEnemyEtis_[i] = NEW EnemyEtis("Etis01");
        apEnemyEtis_[i]->inactivate();
        appendFormationMember(apEnemyEtis_[i] );
    }
}

void FormationEtis001::initialize() {
    for (int i = 0; i < NUM_ETIS_FORMATION001; i++) {
        apEnemyEtis_[i]->activateDelay(i * 20 + 1);
    }
}

FormationEtis001::~FormationEtis001() {
}
