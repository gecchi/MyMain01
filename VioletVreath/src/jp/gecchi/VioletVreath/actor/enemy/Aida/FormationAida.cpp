#include "stdafx.h"
#include "FormationAida.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/EnemyAida.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAida::FormationAida(const char* prm_name) : FkFormation(prm_name) {
    _class_name = "FormationAida";

}
void FormationAida::onActive() {
    while (canCallUp()) {
        EnemyAida* pAida = (EnemyAida*)callUpMember();
        if (pAida) {
            onCallUpAida(pAida); //コールバック
        }
    }
}

void FormationAida::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationAida::~FormationAida() {
}

