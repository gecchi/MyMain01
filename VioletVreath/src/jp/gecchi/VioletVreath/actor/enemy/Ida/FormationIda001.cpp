#include "FormationIda001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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

    coord r = PX_C(150);
    for (angle rx = D90ANG; rx <= D270ANG;  rx += (D_ANG(20))) {
        coord Y = ANG_SIN(rx) * r;
        coord r2 = ANG_COS(rx) * r;
        for (angle ry = 0; ry < D360ANG;  ry += (D_ANG(20))) {
            coord X = ANG_COS(ry) * r2;
            coord Z = ANG_SIN(ry) * r2;
            EnemyIda* pIda = NEW EnemyIda("Ida01");
            addFormationMember(pIda,X,Y,Z,0,0,0);
        }

    }
}

void FormationIda001::onCallUpIda(EnemyIda* pEnemyIda) {
}

void FormationIda001::processBehavior() {
    FormationIda::processBehavior();
}

FormationIda001::~FormationIda001() {
}
