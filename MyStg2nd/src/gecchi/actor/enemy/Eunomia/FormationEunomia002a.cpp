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
//    pEnemyEunomia->_pSplSeq->adjustAxisRate(
//                                        MyShip::_lim_front, //X•ûŒü”{—¦
//                                        MyShip::_lim_top,   //Y•ûŒü”{—¦
//                                        MyShip::_lim_zleft  //Z•ûŒü”{—¦
//                                    );
//    pEnemyEunomia->_pSplSeq->adjustCoodOffset(0, col*50*1000, col*50*1000);
//    pEnemyEunomia->locate(_papSplLineCon[col]->use()->_pSp->_X_basepoint[0], 0, 0);
    pEnemyEunomia->_pKurokoA->setMvVelo(_mv_velo);
}

FormationEunomia002a::~FormationEunomia002a() {
}
