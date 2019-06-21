#include "FormationGeria002.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/actor/supporter/Kago.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationGeria002::FormationGeria002(const char* prm_name) :
        FormationGeria(prm_name, 500) {
    _class_name = "FormationGeria002";

    setPosition(PX_C(8000), 0, PX_C(8000));
    setFaceAngTwd(PX_C(-8000), 0, PX_C(8000));
    callKago()->setVxyzMvVelo(0, 0, -2000);
}

void FormationGeria002::processBehavior() {
    if (getActiveFrame() % 6 == 0) {
        EnemyGeria* pGeria = summonGeria();
        if (pGeria) {
            pGeria->setPositionAroundAt(this, PX_C(800));
            pGeria->callRikisha()->setRzRyMvAng(_rz, _ry); //向いてる方向に飛ばす
            pGeria->callRikisha()->setMvVelo(PX_C(20));
            pGeria->setMigrationLength(PX_C(15000));
        }
    }
    callKago()->behave();
}

void FormationGeria002::processJudgement() {
    Spacetime* pSpacetime =  pGOD->getSpacetime();
    if (_x < pSpacetime->_x_bound_left) {
        _TRACE_(FUNC_NAME<<" 終了");
        sayonara();
    }
}

FormationGeria002::~FormationGeria002() {
}
