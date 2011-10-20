#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationEunomia001b::FormationEunomia001b(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001b";
}

void FormationEunomia001b::processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->_pSplSeq->adjustAxisRate(
//                                        MyShip::_lim_front, //X•ûŒü”{—¦
//                                       -1.0 * MyShip::_lim_top,   //Y•ûŒü”{—¦
//                                        MyShip::_lim_zleft  //Z•ûŒü”{—¦
//                                    );
    pEnemyEunomia->_pSplSeq->adjustCoodOffset(PX2CO(col*50), PX2CO(col*50), PX2CO(col*50));
    pEnemyEunomia->_pSplSeq->adjustAxisYFlip();
    pEnemyEunomia->_pSplSeq->setAbsoluteBeginCoordinate();
}

FormationEunomia001b::~FormationEunomia001b() {
}
