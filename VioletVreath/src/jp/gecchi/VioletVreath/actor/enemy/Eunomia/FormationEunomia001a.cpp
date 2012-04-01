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
//    pEnemyEunomia->pSplSeq_->adjustAxisRate(
//                                        MyShip::lim_front_, //X•ûŒü”{—¦
//                                        MyShip::lim_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_zleft_  //Z•ûŒü”{—¦
//                                    );
    pEnemyEunomia->pSplSeq_->adjustCoodOffset(PXCO(0), PXCO(col*50), PXCO(col*50));
    pEnemyEunomia->pSplSeq_->setAbsoluteBeginCoordinate();
}

FormationEunomia001a::~FormationEunomia001a() {
}
