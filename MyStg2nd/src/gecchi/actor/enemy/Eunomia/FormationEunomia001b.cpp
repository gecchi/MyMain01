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
//    pEnemyEunomia->_pSplProgram->adjustAxisRate(
//                                        MyShip::_lim_front, //X•ûŒü”{—¦
//                                       -1.0 * MyShip::_lim_top,   //Y•ûŒü”{—¦
//                                        MyShip::_lim_zleft  //Z•ûŒü”{—¦
//                                    );
    pEnemyEunomia->_pSplProgram->adjustCoodOffset(col*50*1000, col*50*1000, col*50*1000);
    pEnemyEunomia->_pSplProgram->adjustAxisYFlip();
    pEnemyEunomia->_pSplProgram->setAbsoluteBeginCoordinate();
    pEnemyEunomia->_pKurokoA->setMvVelo(_mv_velo);
}

FormationEunomia001b::~FormationEunomia001b() {
}
