#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe001::FormationHebe001(const char* prm_name) :
        FormationHebe(prm_name, "FormationHebe001") {
    _class_name = "FormationHebe001";
}
void FormationHebe001::processOnActiveHebe(EnemyHebe* pEnemyHebe) {
//    pEnemyHebe->pSplSeq_->adjustAxisRate(
//                                        MyShip::lim_front_, //X�����{��
//                                       -1.0 * MyShip::lim_top_,   //Y�����{��
//                                        MyShip::lim_zleft_  //Z�����{��
//                                    );
//    pEnemyHebe->pSplSeq_->adjustCoodOffset(PX_C(col*50), PX_C(col*50), PX_C(col*50));
//    pEnemyHebe->pSplSeq_->adjustAxisYFlip();
//    pEnemyHebe->pSplSeq_->setAbsoluteBeginCoordinate();
    pEnemyHebe->locate(PX_C(300), PX_C(-300), PX_C(0));
    pEnemyHebe->_pKurokoA->setMvAng(PX_C(300), PX_C(0), PX_C(0));
}

void FormationHebe001::processBehavior() {
    FormationHebe::processBehavior();
}

FormationHebe001::~FormationHebe001() {
}