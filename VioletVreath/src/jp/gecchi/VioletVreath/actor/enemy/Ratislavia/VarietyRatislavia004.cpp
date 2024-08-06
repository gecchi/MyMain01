#include "VarietyRatislavia004.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Omulus/EnemyOmulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia004::VarietyRatislavia004(const char* prm_name) : EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia004";
    for (angle ang1 = D0ANG; ang1 < D360ANG;  ang1 += D_ANG(20)) {
        for (angle ang2 = D0ANG; ang2 < D360ANG;  ang2 += D_ANG(20)) {
            EnemyOmulus* p = NEW EnemyOmulus("pEV1");
            appendGroupChildAsFkOnSurface(p, ang1, ang2);
            Sleep(1);
        }
    }
}

void VarietyRatislavia004::initialize() {
    EnemyRatislavia::initialize();
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    _x = pSpacetime->_x_bound_right + r1_*2 + r2_*2;
    _y = MyShip::lim_y_bottom_;
    _z = 0;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRzRyMvAng(D180ANG, 0);
    pLocusVehicle->setMvVelo(3000);
    pLocusVehicle->setFaceAngVelo(AXIS_Z, -20);
    pLocusVehicle->setFaceAngVelo(AXIS_Y, 10);
}

void VarietyRatislavia004::processBehavior() {
    EnemyRatislavia::processBehavior();
}

VarietyRatislavia004::~VarietyRatislavia004() {
}
