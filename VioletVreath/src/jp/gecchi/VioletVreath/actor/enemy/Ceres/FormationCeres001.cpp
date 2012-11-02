#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationCeres001::FormationCeres001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationCeres001";
    for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
        pEnemyCeres_[i] = NEW EnemyCeres("Ceres01");
        pEnemyCeres_[i]->inactivateImmed();
        addSubLast(pEnemyCeres_[i] );
    }
}

void FormationCeres001::initialize() {
    for (int i = 0; i < NUM_CERES_FORMATION001; i++) {
        pEnemyCeres_[i]->activateDelay(i * 30 + 1);
    }
}

void FormationCeres001::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    GgafDxGeometricActor* pActor_LastDestroyed = (GgafDxGeometricActor*)prm_pActor_LastDestroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_LastDestroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_LastDestroyed);
}

FormationCeres001::~FormationCeres001() {
}
