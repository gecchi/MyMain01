#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia001a::FormationEunomia001a(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001a";
}
void FormationEunomia001a::onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pKurokoStepper_->adjustAxisRate(
//                                        MyShip::lim_front_, //X•ûŒü”{—¦
//                                        MyShip::lim_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_zleft_  //Z•ûŒü”{—¦
//                                    );
    pEnemyEunomia->pKurokoStepper_->adjustCoordOffset(PX_C(0), PX_C(col*50), PX_C(col*50));
    pEnemyEunomia->pKurokoStepper_->setAbsoluteBeginCoord();
}

FormationEunomia001a::~FormationEunomia001a() {
}
