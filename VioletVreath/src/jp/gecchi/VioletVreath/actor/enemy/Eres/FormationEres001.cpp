#include "FormationEres001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEres.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationEres001::FormationEres001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationEres001";
    for (int i = 0; i < 1; i++) {
        appendFormationMember(NEW EnemyEres("Eres"));
    }
}

void FormationEres001::initialize() {
}

void FormationEres001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % 32U == 0) {
        callUpMember();
    }
}

void FormationEres001::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationEres001::~FormationEres001() {
}
