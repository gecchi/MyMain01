#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001b::FormationPallas001b(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001b";
}
void FormationPallas001b::onActive() {
    for (int i = 0; i < _num_Pallas; i++) {
//        _papPallas[i]->_pSplSeqram->adjustAxisRate(
//                                            MyShip::_lim_front, //X�����{��
//                                           -MyShip::_lim_top,   //Y�����{��
//                                            MyShip::_lim_zleft  //Z�����{��
//                                        );
        _papPallas[i]->_pSplSeqram->setAbsoluteBeginCoordinate();
        _papPallas[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papPallas[i]->activateDelay(i*_interval_frames + 1);//_interval_frames�Ԋu��Active�ɂ���B
    }
}

FormationPallas001b::~FormationPallas001b() {
}
