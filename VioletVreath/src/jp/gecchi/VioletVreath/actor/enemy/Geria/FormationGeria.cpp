#include "FormationGeria.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/GeoDriver.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationGeria::FormationGeria(
            const char* prm_name,
            int prm_nGeriaStock
            ) : DefaultGeometricActor(prm_name) {
    _class_name = "FormationGeria";
    pDepo_ = NEW GgafCore::ActorDepository("RotEnemyGeria");
    for (int i = 0; i < prm_nGeriaStock; i++) {
        std::string name = "Geria"+XTOS(i);
        EnemyGeria* pEnemyGeria = NEW EnemyGeria(name.c_str());
        pEnemyGeria->getVecDriver()->linkFaceAngByMvAng(true);
        pDepo_->put(pEnemyGeria);
    }
    appendGroupChild(pDepo_);
}

EnemyGeria* FormationGeria::summonGeria() {
    EnemyGeria* pGeria = (EnemyGeria*)pDepo_->dispatch();
    return pGeria;
}

FormationGeria::~FormationGeria() {
}
