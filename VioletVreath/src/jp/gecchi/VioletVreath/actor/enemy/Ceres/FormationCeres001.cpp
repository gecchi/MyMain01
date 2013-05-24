#include "stdafx.h"
#include "FormationCeres001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/EnemyCeres.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationCeres001::FormationCeres001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationCeres001";
    for (int i = 0; i < 10; i++) {
        addFormationMember(NEW EnemyCeres("Ceres"));
    }
}

void FormationCeres001::initialize() {
}

void FormationCeres001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % 32 == 0) {
        callUpMember();
    }
}

void FormationCeres001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationCeres001::~FormationCeres001() {
}
