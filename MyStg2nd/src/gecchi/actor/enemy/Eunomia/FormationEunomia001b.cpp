#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia001b::FormationEunomia001b(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001b";
}

void FormationEunomia001b::processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) {
    pEnemyEunomia->_pSplineProgram->adjustAxisRate(1.0, -1.0, 1.0);
    pEnemyEunomia->_pSplineProgram->adjustAxisOffset(col*50*1000, col*50*1000, col*50*1000);
    pEnemyEunomia->_pSplineProgram->setAbsoluteBeginCoordinate();
    pEnemyEunomia->_pMover->setMvVelo(_mv_velo);
}

FormationEunomia001b::~FormationEunomia001b() {
}