#include "FormationOebius.h"

#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "EnemyOebiusCore.h"
#include "EnemyOebiusController.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationOebius::FormationOebius(const char* prm_name, EnemyOebiusController* prm_pController) :
        VvFormationActor<TreeFormation>(prm_name) {
    _class_name = "FormationOebius";
    pController_ = prm_pController;
}

void FormationOebius::scatterMember() {
    EnemyOebius* pOebius = (EnemyOebius*)getChildFirst();
    while (pOebius) {
        pOebius->scatter();
        if (pOebius->isLast()) {
            break;
        } else {
            pOebius = (EnemyOebius*)(pOebius->getNext());
        }
    }
}

void FormationOebius::onSayonaraAll() {
    pController_->pFormationOebius_ = nullptr;
}

FormationOebius::~FormationOebius() {

}
