#include "VarietyRatislavia002.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emus/EnemyEmus.h"



using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia002::VarietyRatislavia002(const char* prm_name) :
        EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia002";
    for (angle ang1 = 0; ang1 < D360ANG;  ang1 += (D_ANG(20))) {
        for (angle ang2 = 0; ang2 < D360ANG;  ang2 += (D_ANG(20))) {
            std::string name = "Emus(" + XTOS(ang1) + "," + XTOS(ang2) + ")";
            EnemyEmus* p = NEW EnemyEmus(name.c_str());
            appendChildAsFkOnSurface(p, ang1, ang2);
            p->ini_wait_ = ( ((ang2/D_ANG(20)) * (D360ANG/D_ANG(20))) + (ang1/D_ANG(20)) ) * 3;
            Sleep(1);
        }
    }
}

void VarietyRatislavia002::initialize() {
    EnemyRatislavia::initialize();
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    _x = pSpacetime->_x_bound_right + r1_*2 + r2_*2;
    _y = 0;
    _z = MyShip::lim_z_left_;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRzRyMvAng(D180ANG, 0);
    pLocusVehicle->setMvVelo(1000);
    pLocusVehicle->setFaceAngVelo(AXIS_X, 10);
    pLocusVehicle->setFaceAngVelo(AXIS_Z, -50);
    pLocusVehicle->setFaceAngVelo(AXIS_Y, 30);
}

void VarietyRatislavia002::processBehavior() {
    EnemyRatislavia::processBehavior();
}


VarietyRatislavia002::~VarietyRatislavia002() {
}
