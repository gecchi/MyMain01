#include "FormationGeria001.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/actor/supporter/Kago.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationGeria001::FormationGeria001(const char* prm_name) :
        FormationGeria(prm_name, 500) {
    _class_name = "FormationGeria001";

    setPosition(PX_C(5000), 0, PX_C(5000));
    setFaceAngTwd(PX_C(5000), 0, -PX_C(5000));
    callKago()->setVxyzMvVelo(-2000, 0, 0);
}

void FormationGeria001::processBehavior() {
    if (getActiveFrame() % 6 == 0) {
        EnemyGeria* pGeria = summonGeria();
        if (pGeria) {
            pGeria->setPositionAroundAt(this, PX_C(800));
            pGeria->callRikisha()->setRzRyMvAng(_rz, _ry); //向いてる方向に飛ばす
            pGeria->callRikisha()->setMvVelo(PX_C(20));
            pGeria->setMigrationLength(PX_C(10000));
        }
    }
    callKago()->behave();
}

void FormationGeria001::processJudgement() {
    Spacetime* pSpacetime =  pGOD->getSpacetime();
    if (_x < pSpacetime->_x_bound_left) {
        _TRACE_(FUNC_NAME<<" 終了");
        sayonara();
    }
}

FormationGeria001::~FormationGeria001() {
}
