#include "FormationEres002.h"

#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEres.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEres002::FormationEres002(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationEres002";

    for (int i = 0; i < 30; i++) {
        EnemyEres* pEres = NEW EnemyEres("Eres");
        pEres->Y_turn_ = -1*(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2) + (i * ((PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT)/30));
        pEres->_z = -1500000;
        addFormationMember(pEres);
    }
}

void FormationEres002::initialize() {
}

void FormationEres002::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % 64 == 0) {
        EnemyEres* pEres = (EnemyEres*)callUpMember();
        if (pEres) {
            pEres->activate();
        }
    }
}

void FormationEres002::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationEres002::~FormationEres002() {
}
