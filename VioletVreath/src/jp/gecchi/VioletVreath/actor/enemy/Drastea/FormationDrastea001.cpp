#include "FormationDrastea001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Drastea/EnemyDrastea.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationDrastea001::FormationDrastea001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationDrastea001";
    for (int i = 0; i < 10; i++) {
        appendFormationMember(NEW EnemyDrastea("Drastea01"));
    }
}

void FormationDrastea001::initialize() {
}

void FormationDrastea001::processBehavior() {
    if (canCalledUp() && (getActiveFrame()-1) % 32 == 0) {
        calledUpMember();
    }
}

FormationDrastea001::~FormationDrastea001() {
}
