#include "FormationIda.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/EnemyIda.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/GeoElem.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationIda::FormationIda(const char* prm_name) : VvFormationActor<FkFormation>(prm_name) {
    _class_name = "FormationIda";

}
void FormationIda::onActive() {
    while (canSummon()) {
        EnemyIda* pIda = (EnemyIda*)summonMember();
        if (pIda) {
            onSummonIda(pIda); //コールバック
        }
    }
}

FormationIda::~FormationIda() {
}

