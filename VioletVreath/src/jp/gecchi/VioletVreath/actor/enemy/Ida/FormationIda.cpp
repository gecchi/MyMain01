#include "stdafx.h"
#include "FormationIda.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/EnemyIda.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIda::FormationIda(const char* prm_name) : FkFormation(prm_name) {
    _class_name = "FormationIda";

}
void FormationIda::onActive() {
    while (canCallUp()) {
        EnemyIda* pIda = (EnemyIda*)callUpMember();
        if (pIda) {
            onCallUpIda(pIda); //コールバック
        }
    }
}

void FormationIda::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationIda::~FormationIda() {
}

