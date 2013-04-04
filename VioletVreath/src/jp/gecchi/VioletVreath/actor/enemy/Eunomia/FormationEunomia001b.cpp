#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia001b::FormationEunomia001b(const char* prm_name) : FormationEunomia001(prm_name) {
    _class_name = "FormationEunomia001b";
}

void FormationEunomia001b::onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) {
//    pEnemyEunomia->pKurokoStepper_->adjustAxisRate(
//                                        MyShip::lim_front_, //X•ûŒü”{—¦
//                                       -1.0 * MyShip::lim_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_zleft_  //Z•ûŒü”{—¦
//                                    );
    pEnemyEunomia->pKurokoStepper_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
    pEnemyEunomia->pKurokoStepper_->adjustAxisYFlip();
    pEnemyEunomia->pKurokoStepper_->setAbsoluteBeginCoord();
}

FormationEunomia001b::~FormationEunomia001b() {
}
