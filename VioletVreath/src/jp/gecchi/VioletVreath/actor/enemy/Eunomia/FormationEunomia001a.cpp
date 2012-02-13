#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia001a::FormationEunomia001a(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001a";
}
void FormationEunomia001a::processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->_pSplSeq->adjustAxisRate(
//                                        MyShip::_lim_front, //X�����{��
//                                        MyShip::_lim_top,   //Y�����{��
//                                        MyShip::_lim_zleft  //Z�����{��
//                                    );
    pEnemyEunomia->_pSplSeq->adjustCoodOffset(PX2CO(0), PX2CO(col*50), PX2CO(col*50));
    pEnemyEunomia->_pSplSeq->setAbsoluteBeginCoordinate();
}

FormationEunomia001a::~FormationEunomia001a() {
}
