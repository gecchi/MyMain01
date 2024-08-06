#include "FormationGeria001.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/EnemyGeria.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationGeria001::FormationGeria001(const char* prm_name) :
        FormationGeria(prm_name, 500) {
    _class_name = "FormationGeria001";

    setPosition(PX_C(5000), 0, PX_C(5000));
    setFaceAngTwd(PX_C(5000), 0, -PX_C(5000));
    getCoordVehicle()->setVeloXYZ(-2000, 0, 0);
}

void FormationGeria001::processBehavior() {
    if (getActiveFrame() % 6 == 0) {
        EnemyGeria* pGeria = summonGeria();
        if (pGeria) {
            pGeria->setPositionAroundAt(this, PX_C(800));
            pGeria->getLocusVehicle()->setRzRyMvAng(_rz, _ry); //Œü‚¢‚Ä‚é•ûŒü‚É”ò‚Î‚·
            pGeria->getLocusVehicle()->setMvVelo(PX_C(20));
            pGeria->setMigrationLength(PX_C(10000));
        }
    }
    getCoordVehicle()->behave();
}

void FormationGeria001::processJudgement() {
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    if (_x < pSpacetime->_x_bound_left) {
        _TRACE_(FUNC_NAME<<" I—¹");
        sayonara();
    }
}

FormationGeria001::~FormationGeria001() {
}
