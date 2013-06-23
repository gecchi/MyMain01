#include "stdafx.h"
#include "FormationAida001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/EnemyAida.h"
#include "EnemyAidaBase001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAida001::FormationAida001(const char* prm_name) :
        FormationAida(prm_name) {
    _class_name = "FormationAida001";
    setFkBase(NEW EnemyAidaBase001("Base"));

    coord r = PX_C(100);
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (D_ANG(30))) {
        coord X = 0;
        coord Y = ANG_SIN(angPos1) * r;
        coord Z = ANG_COS(angPos1) * r;
        EnemyAida* pAida = NEW EnemyAida("Aida01");
        addFormationMemberAsFk(pAida,X,Y,Z,0,0,0);
    }
}

void FormationAida001::onCallUpAida(EnemyAida* pEnemyAida) {
}

void FormationAida001::processBehavior() {
    FormationAida::processBehavior();
}

FormationAida001::~FormationAida001() {
}
