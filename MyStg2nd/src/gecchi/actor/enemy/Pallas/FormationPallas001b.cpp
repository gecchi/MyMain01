#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001b::FormationPallas001b(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001b";
}
void FormationPallas001b::initialize() {
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i]->_pSplineProgram->setRate(1.0, -1.0, 1.0);
        _papPallas[i]->setGeometry(_pSplineCon->refer()->_X_basepoint[0] ,
                                   0,
                                   0);
        _papPallas[i]->_pMover->setMvVelo(_mv_velo);
        _papPallas[i]->activateAfter(i*_frame_interval + 1);//_frame_intervalä‘äuÇ≈ActiveÇ…Ç∑ÇÈÅB
    }
}

FormationPallas001b::~FormationPallas001b() {
}
