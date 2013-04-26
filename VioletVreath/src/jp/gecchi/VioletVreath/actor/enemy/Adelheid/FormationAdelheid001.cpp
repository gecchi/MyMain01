#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAdelheid001::FormationAdelheid001(const char* prm_name) :
        FormationAdelheid(prm_name) {
    _class_name = "FormationAdelheid001";

    pSplManufConnection_ = connectToSplineManufactureManager("FormationAdelheid001");

}
void FormationAdelheid001::onCallUpAdelheid(EnemyAdelheid* pEnemyAdelheid) {
//    pEnemyAdelheid->pKurokoLeader_->adjustAxisRate(
//                                        MyShip::lim_front_, //X•ûŒü”{—¦
//                                       -1.0 * MyShip::lim_top_,   //Y•ûŒü”{—¦
//                                        MyShip::lim_zleft_  //Z•ûŒü”{—¦
//                                    );
//    pEnemyAdelheid->pKurokoLeader_->adjustCoordOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyAdelheid->pKurokoLeader_->adjustAxisYFlip();
//    pEnemyAdelheid->pKurokoLeader_->setAbsoluteBeginCoord();
    pEnemyAdelheid->locate(PX_C(300), PX_C(-300), PX_C(500));
    pEnemyAdelheid->_pKurokoA->setMvAngTwd(PX_C(300), PX_C(0), PX_C(500));
}
GgafLib::SplineManufacture* FormationAdelheid001::getFormationSplManuf() {
    return pSplManufConnection_->peek(); //e
}
void FormationAdelheid001::processBehavior() {
    FormationAdelheid::processBehavior();
}

FormationAdelheid001::~FormationAdelheid001() {
    pSplManufConnection_->close();
}
