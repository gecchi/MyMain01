#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001a::FormationPallas001a(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001a";
}
void FormationPallas001a::onActive() {
    for (int i = 0; i < num_Pallas_; i++) {
//        papPallas_[i]->pSplSeq_->adjustAxisRate(
//                                            MyShip::lim_front_, //Xï˚å¸î{ó¶
//                                            MyShip::lim_top_,   //Yï˚å¸î{ó¶
//                                            MyShip::lim_zleft_  //Zï˚å¸î{ó¶
//                                        );
        papPallas_[i]->pSplSeq_->setAbsoluteBeginCoordinate();
        papPallas_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papPallas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_ä‘äuÇ≈ActiveÇ…Ç∑ÇÈÅB
    }
}

FormationPallas001a::~FormationPallas001a() {
}
