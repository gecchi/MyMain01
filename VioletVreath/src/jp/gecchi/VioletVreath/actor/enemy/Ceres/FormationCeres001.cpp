#include "stdafx.h"
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
    if (canCallUp() && (getActivePartFrame()-1) % 30 == 0) {
        callUpMember();
    }
}

void FormationCeres001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（※ボーナススコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationCeres001::~FormationCeres001() {
}
