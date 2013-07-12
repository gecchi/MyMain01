#include "stdafx.h"
#include "FormationThagoras.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras::FormationThagoras(const char* prm_name, int prm_num_Thagoras) :
        TreeFormation(prm_name) {
    _class_name = "FormationThagoras";
    num_Thagoras_    = prm_num_Thagoras;  //ï“ë‡êî
    for (int i = 0; i < num_Thagoras_; i++) {
        std::string name = "Thagoras("+XTOS(i)+")";
        addFormationMember(NEW EnemyThagoras(name.c_str()));
    }
}
void FormationThagoras::initialize() {
}

void FormationThagoras::onActive() {
}

void FormationThagoras::processBehavior() {
}

void FormationThagoras::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationThagoras::~FormationThagoras() {
}
