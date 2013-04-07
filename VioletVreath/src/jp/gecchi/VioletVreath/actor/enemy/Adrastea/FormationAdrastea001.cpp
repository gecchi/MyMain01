#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAdrastea001::FormationAdrastea001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationAdrastea001";
    for (int i = 0; i < 10; i++) {
        addFormationMember(NEW EnemyAdrastea("Adrastea01"));
    }
}

void FormationAdrastea001::initialize() {
}

void FormationAdrastea001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % 32 == 0) {
        callUpMember();
    }
}

FormationAdrastea001::~FormationAdrastea001() {
}
