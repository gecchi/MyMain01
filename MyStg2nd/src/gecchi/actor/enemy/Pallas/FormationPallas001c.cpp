#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001c::FormationPallas001c(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001c";
}
void FormationPallas001c::onActive() {
    for (int i = 0; i < _num_Pallas; i++) {
//        _papPallas[i]->_pSplProgram->adjustAxisRate(
//                                            MyShip::_lim_front, //Xï˚å¸î{ó¶
//                                            MyShip::_lim_top,   //Yï˚å¸î{ó¶
//                                           -MyShip::_lim_zleft  //Zï˚å¸î{ó¶
//                                        );
        _papPallas[i]->_pSplProgram->setAbsoluteBeginCoordinate();
        _papPallas[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papPallas[i]->activateDelay(i*_interval_frames + 1);//_interval_framesä‘äuÇ≈ActiveÇ…Ç∑ÇÈÅB
    }
}

FormationPallas001c::~FormationPallas001c() {
}
