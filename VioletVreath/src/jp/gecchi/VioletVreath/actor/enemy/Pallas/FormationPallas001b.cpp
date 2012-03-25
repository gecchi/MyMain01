#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001b::FormationPallas001b(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001b";
}
void FormationPallas001b::onActive() {
    for (int i = 0; i < num_Pallas_; i++) {
//        papPallas_[i]->pSplSeq_->adjustAxisRate(
//                                            MyShip::lim_front_, //X�����{��
//                                           -MyShip::lim_top_,   //Y�����{��
//                                            MyShip::lim_zleft_  //Z�����{��
//                                        );
        papPallas_[i]->pSplSeq_->adjustAxisYFlip();
        papPallas_[i]->pSplSeq_->setAbsoluteBeginCoordinate();
        papPallas_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papPallas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

FormationPallas001b::~FormationPallas001b() {
}