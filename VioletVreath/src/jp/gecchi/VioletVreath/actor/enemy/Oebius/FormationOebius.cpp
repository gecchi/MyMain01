#include "FormationOebius.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "EnemyOebiusCore.h"
#include "EnemyOebiusController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOebius::FormationOebius(const char* prm_name, EnemyOebiusController* prm_pController) :
        TreeFormation(prm_name) {
    _class_name = "FormationOebius";
    pController_ = prm_pController;
}

void FormationOebius::scatterMember() {
    EnemyOebius* pOebius = (EnemyOebius*)getSubFirst();
    while (pOebius) {
        pOebius->scatter();
        if (pOebius->isLast()) {
            break;
        } else {
            pOebius = (EnemyOebius*)(pOebius->getNext());
        }
    }
}

void FormationOebius::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}
void FormationOebius::onSayonaraAll() {
    pController_->pFormationOebius_ = nullptr;
}

FormationOebius::~FormationOebius() {

}
