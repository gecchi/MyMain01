#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia002b::FormationEunomia002b(const char* prm_name) : FormationEunomia002(prm_name) {
    _class_name = "FormationEunomia002b";
}

void FormationEunomia002b::processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) {
    pEnemyEunomia->_pSplineProgram->adjustAxisRate(1.0, -1.0, 1.0);
    pEnemyEunomia->setCoordinate(_papSplineCon[col]->refer()->_pSp->_X_basepoint[0], 0, 0);
    pEnemyEunomia->_pMover->setMvVelo(_mv_velo);
}

FormationEunomia002b::~FormationEunomia002b() {
}
