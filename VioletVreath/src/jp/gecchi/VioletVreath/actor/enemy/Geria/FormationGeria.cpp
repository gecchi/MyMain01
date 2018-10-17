#include "FormationGeria.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationGeria::FormationGeria(
            const char* prm_name,
            int prm_nGeriaStock
            ) : DefaultGeometricActor(prm_name, nullptr) {
    _class_name = "FormationGeria";
    pDepo_ = NEW GgafActorDepository("RotEnemyGeria");
    for (int i = 0; i < prm_nGeriaStock; i++) {
        std::string name = "Geria"+XTOS(i);
        EnemyGeria* pEnemyGeria = NEW EnemyGeria(name.c_str());
        pEnemyGeria->getKuroko()->linkFaceAngByMvAng(true);
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
