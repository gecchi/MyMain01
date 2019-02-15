#include "EnemyAntiopeP.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyAntiopeP::EnemyAntiopeP(const char* prm_name) :
        EnemyAntiope(prm_name, "Antiope") {
    getStatus()->reset(statusResetFunction(EnemyAntiope));
    setMaterialColor(1.0,0.2,0.2);
}

EnemyAntiopeP::~EnemyAntiopeP() {
}
