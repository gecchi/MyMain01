#include "EnemyAntiopeN.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyAntiopeN::EnemyAntiopeN(const char* prm_name) :
        EnemyAntiope(prm_name, "Antiope", STATUS(EnemyAntiope)) {
    setMaterialColor(0.2,0.2,1.0);
}

EnemyAntiopeN::~EnemyAntiopeN() {
}
