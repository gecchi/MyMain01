#include "FormationEres001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEres.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationEres001::FormationEres001(const char* prm_name) : VvFormationActor<TreeFormation>(prm_name) {
    _class_name = "FormationEres001";
    for (int i = 0; i < 10; i++) {
        appendFormationMember(NEW EnemyEres("Eres"));
    }
}

void FormationEres001::initialize() {
}

void FormationEres001::processBehavior() {
    if (canSummon() && (getActiveFrame()-1) % 32U == 0) {
        summonMember();
    }
}

FormationEres001::~FormationEres001() {
}
