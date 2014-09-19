#include "FormationOebius.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/util/XpmHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOebius::FormationOebius(const char* prm_name, int prm_formation_row_num) :
        TreeFormation(prm_name) {
    _class_name = "FormationOebius";
    formation_row_num_ = prm_formation_row_num;
    num_Oebius_ = formation_row_num_ * 40;
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        addFormationMember(NEW EnemyOebius(name.c_str()));
    }

    call_up_interval_ = 15; //oŒ»ŠÔŠu

}

void FormationOebius::initialize() {
}

void FormationOebius::onActive() {
}

void FormationOebius::processBehavior() {
    if (canCallUp()) {
        if (getActiveFrame() % call_up_interval_ == 0) {
            for (int row = 0; row < formation_row_num_; row++) {
                EnemyOebius* pOebius = (EnemyOebius*)callUpMember();
                if (pOebius) {
                    onCallUp(pOebius, row);
                }
            }
        }
    }
}

void FormationOebius::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationOebius::~FormationOebius() {
}
