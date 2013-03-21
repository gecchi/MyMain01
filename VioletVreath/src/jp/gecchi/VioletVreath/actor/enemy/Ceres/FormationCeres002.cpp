#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationCeres002::FormationCeres002(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationCeres002";

    for (int i = 0; i < 30; i++) {
        EnemyCeres* pCeres = NEW EnemyCeres("Ceres");
        pCeres->Y_turn_ = -1*(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2) + (i * ((PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT)/30));
        pCeres->_Z = -1500000;
        addFormationMember(pCeres);
    }
}

void FormationCeres002::initialize() {
}

void FormationCeres002::processBehavior() {
    if (canCallUp() && (getActivePartFrame()-1) % 80 == 0) {
        EnemyCeres* pCeres = (EnemyCeres*)callUp();
        if (pCeres) {
            pCeres->activate();
        }
    }
}

void FormationCeres002::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationCeres002::~FormationCeres002() {
}
