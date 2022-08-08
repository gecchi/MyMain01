#include "FormationIda.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/EnemyIda.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/GeoElem.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationIda::FormationIda(const char* prm_name) : FkFormation(prm_name) {
    _class_name = "FormationIda";

}
void FormationIda::onActive() {
    while (canCalledUp()) {
        EnemyIda* pIda = (EnemyIda*)calledUpMember();
        if (pIda) {
            onCalledUpIda(pIda); //�R�[���o�b�N
        }
    }
}

void FormationIda::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationIda::~FormationIda() {
}

