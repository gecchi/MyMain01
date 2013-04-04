#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe001::FormationHebe001(const char* prm_name) :
        FormationHebe(prm_name, "FormationHebe001") {
    _class_name = "FormationHebe001";
}
void FormationHebe001::onCallUpHebe(EnemyHebe* pEnemyHebe) {
//    pEnemyHebe->pKurokoStepper_->adjustAxisRate(
//                                        MyShip::lim_front_, //X�����{��
//                                       -1.0 * MyShip::lim_top_,   //Y�����{��
//                                        MyShip::lim_zleft_  //Z�����{��
//                                    );
//    pEnemyHebe->pKurokoStepper_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyHebe->pKurokoStepper_->adjustAxisYFlip();
//    pEnemyHebe->pKurokoStepper_->setAbsoluteBeginCoord();
    pEnemyHebe->locate(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyHebe->_pKurokoA->setMvAngTwd(PX_C(300), PX_C(0), PX_C(0));
}

void FormationHebe001::processBehavior() {
    FormationHebe::processBehavior();
}

FormationHebe001::~FormationHebe001() {
}
