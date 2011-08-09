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
//    pEnemyEunomia->_pSplSeqram->adjustAxisRate(
//                                        MyShip::_lim_front, //X•ûŒü”{—¦
//                                       -1.0 * MyShip::_lim_top,   //Y•ûŒü”{—¦
//                                        MyShip::_lim_zleft  //Z•ûŒü”{—¦
//                                    );
    pEnemyEunomia->_pSplSeqram->adjustCoodOffset(col*50*1000, col*50*1000, col*50*1000);
    pEnemyEunomia->_pSplSeqram->adjustAxisYFlip();
    pEnemyEunomia->_pSplSeqram->setAbsoluteBeginCoordinate();
    pEnemyEunomia->_pKurokoA->setMvVelo(_mv_velo);
}

FormationEunomia001b::~FormationEunomia001b() {
}
