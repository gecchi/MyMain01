#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia001a::FormationEunomia001a(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001a";
}
void FormationEunomia001a::onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pSplSeq_->adjustAxisRate(
//                                        MyShip::lim_front_, //X�����{��
//                                        MyShip::lim_top_,   //Y�����{��
//                                        MyShip::lim_zleft_  //Z�����{��
//                                    );
    pEnemyEunomia->pSplSeq_->adjustCoordOffset(PX_C(0), PX_C(col*50), PX_C(col*50));
    pEnemyEunomia->pSplSeq_->setAbsoluteBeginCoordinate();
}

FormationEunomia001a::~FormationEunomia001a() {
}
