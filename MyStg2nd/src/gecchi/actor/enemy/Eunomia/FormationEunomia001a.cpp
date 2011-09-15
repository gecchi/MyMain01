#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia001a::FormationEunomia001a(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001a";
}
void FormationEunomia001a::processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->_pSplSeq->adjustAxisRate(
//                                        MyShip::_lim_front, //X�����{��
//                                        MyShip::_lim_top,   //Y�����{��
//                                        MyShip::_lim_zleft  //Z�����{��
//                                    );
    pEnemyEunomia->_pSplSeq->adjustCoodOffset(0, col*50*1000, col*50*1000);
    pEnemyEunomia->_pSplSeq->setAbsoluteBeginCoordinate();
}

FormationEunomia001a::~FormationEunomia001a() {
}
