#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAntiopeP::EnemyAntiopeP(const char* prm_name) :
        EnemyAntiope(prm_name, "Antiope", STATUS(EnemyAntiope)) {
    setMaterialColor(1.0,0.2,0.2);
}

EnemyAntiopeP::~EnemyAntiopeP() {
}
