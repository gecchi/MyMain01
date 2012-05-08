#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001c::FormationPallas001c(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001c";
}
void FormationPallas001c::onActive() {
    for (int i = 0; i < num_Pallas_; i++) {
//        papPallas_[i]->pSplSeq_->adjustAxisRate(
//                                            MyShip::lim_front_, //X�����{��
//                                            MyShip::lim_top_,   //Y�����{��
//                                           -MyShip::lim_zleft_  //Z�����{��
//                                        );
        papPallas_[i]->pSplSeq_->adjustAxisZFlip();
        papPallas_[i]->pSplSeq_->setAbsoluteBeginCoordinate();
        papPallas_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papPallas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

FormationPallas001c::~FormationPallas001c() {
}
