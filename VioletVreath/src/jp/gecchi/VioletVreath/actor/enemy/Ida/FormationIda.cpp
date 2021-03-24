#include "FormationIda.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/EnemyIda.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/GeoElem.h"



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

void FormationIda::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationIda::~FormationIda() {
}

