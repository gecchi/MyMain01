#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001d::FormationPallas001d(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001d";
}
void FormationPallas001d::onActive() {
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i]->_pSplineProgram->adjustAxisRate(1.0, -1.0, -1.0);
        _papPallas[i]->locate(_pSplineCon->refer()->_pSp->_X_basepoint[0] ,
                                   0,
                                   0);
        _papPallas[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papPallas[i]->activateDelay(i*_interval_frames + 1);//_interval_framesä‘äuÇ≈ActiveÇ…Ç∑ÇÈÅB
    }
}

FormationPallas001d::~FormationPallas001d() {
}
