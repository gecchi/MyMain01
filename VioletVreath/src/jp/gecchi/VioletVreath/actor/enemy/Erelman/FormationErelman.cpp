#include "FormationErelman.h"

#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/EnemyErelman.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "EnemyErelmanCore.h"
#include "EnemyErelmanController.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationErelman::FormationErelman(const char* prm_name, EnemyErelmanController* prm_pController) :
        TreeFormation(prm_name) {
    _class_name = "FormationErelman";
    pController_ = prm_pController;
}

void FormationErelman::initialize() {
}


void FormationErelman::processBehavior() {
}

void FormationErelman::scatterMember() {
    EnemyErelman* pErelman = (EnemyErelman*)getChildFirst();
    while (pErelman) {
        pErelman->scatter();
        if (pErelman->isLast()) {
            break;
        } else {
            pErelman = (EnemyErelman*)(pErelman->getNext());
        }
    }
}

void FormationErelman::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}
void FormationErelman::onSayonaraAll() {
    pController_->pFormationErelman_ = nullptr;
}

FormationErelman::~FormationErelman() {
}
