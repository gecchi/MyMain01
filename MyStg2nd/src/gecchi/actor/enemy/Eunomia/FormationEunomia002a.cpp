#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia002a::FormationEunomia002a(const char* prm_name) : FormationEunomia002(prm_name) {
    _class_name = "FormationEunomia002a";
}
void FormationEunomia002a::processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) {
    pEnemyEunomia->_pSplineProgram->adjustAxisRate(1.0, 1.0, 1.0);
    pEnemyEunomia->_pSplineProgram->adjustAxisOffset(0, col*50*1000, col*50*1000);
    pEnemyEunomia->locate(_papSplineCon[col]->refer()->_pSp->_X_basepoint[0], 0, 0);
    pEnemyEunomia->_pKurokoA->setMvVelo(_mv_velo);
}

FormationEunomia002a::~FormationEunomia002a() {
}
