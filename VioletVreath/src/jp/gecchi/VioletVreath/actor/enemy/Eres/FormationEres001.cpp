#include "FormationEres001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEres.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEres001::FormationEres001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationEres001";
    for (int i = 0; i < 100; i++) {
        addFormationMember(NEW EnemyEres("Eres"));
    }
}

void FormationEres001::initialize() {
}

void FormationEres001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % 32U == 0) {
        callUpMember();
    }
}

void FormationEres001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

FormationEres001::~FormationEres001() {
}
