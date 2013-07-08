#include "stdafx.h"
#include "FormationIda001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/EnemyIda.h"
#include "EnemyIdaBase001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIda001::FormationIda001(const char* prm_name) :
        FormationIda(prm_name) {
    _class_name = "FormationIda001";
    registerFormationFkBase(NEW EnemyIdaBase001("Base"));

    coord r = PX_C(100);
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (D_ANG(30))) {
        coord X = 0;
        coord Y = ANG_SIN(angPos1) * r;
        coord Z = ANG_COS(angPos1) * r;
        EnemyIda* pIda = NEW EnemyIda("Ida01");
        addFormationMember(pIda,X,Y,Z,0,0,0);
    }
}

void FormationIda001::onCallUpIda(EnemyIda* pEnemyIda) {
}

void FormationIda001::processBehavior() {
    FormationIda::processBehavior();
}

FormationIda001::~FormationIda001() {
}
