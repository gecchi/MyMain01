#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001c::FormationPallas001c(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001c";
}
void FormationPallas001c::initialize() {
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i]->_pSplineProgram->setRate(1.0, 1.0, -1.0);
        _papPallas[i]->setGeometry(_pSplineCon->view()->_X_basepoint[0] ,
                                   0,
                                   0);
        _papPallas[i]->_pMover->setMvVelo(_mv_velo);
        _papPallas[i]->activateAfter(i*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
    }
}

FormationPallas001c::~FormationPallas001c() {
}