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
        _papPallas[i]->_pSplineProgram->adjustAxisRate(1.0, -1.0, 1.0);
        _papPallas[i]->setCoordinate(_pSplineCon->refer()->_pSp->_X_basepoint[0] ,
                                   0,
                                   0);
        _papPallas[i]->_pKuroko->setMvVelo(_mv_velo);
        _papPallas[i]->activateDelay(i*_frame_interval + 1);//_frame_intervalä‘äuÇ≈ActiveÇ…Ç∑ÇÈÅB
    }
}

FormationPallas001b::~FormationPallas001b() {
}
