#include "VarietyRatislavia002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emus/EnemyEmus.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia002::VarietyRatislavia002(const char* prm_name) :
        EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia002";
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (D_ANG(20))) {
        for (angle angPos2 = 0; angPos2 < D360ANG;  angPos2 += (D_ANG(20))) {
            std::string name = "Emus(" + XTOS(angPos1) + "," + XTOS(angPos2) + ")";
            EnemyEmus* p = NEW EnemyEmus(name.c_str());
            addSubGroupAsFkOnSurface(p, angPos1, angPos2);
            p->ini_wait_ = ( ((angPos1/D_ANG(20)) * (D360ANG/D_ANG(20))) + (angPos2/D_ANG(20)) ) * 3;
            Sleep(1);
        }
    }
}

void VarietyRatislavia002::initialize() {
    EnemyRatislavia::initialize();
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    _x = pSpacetime->_x_bound_right + r1_ + r2_;
    _y = 0;
    _z = MyShip::lim_z_left_;
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRzRyMvAng(D180ANG, 0);
    pKuroko->setMvVelo(1000);
    pKuroko->setFaceAngVelo(AXIS_X, 10);
    pKuroko->setFaceAngVelo(AXIS_Z, -50);
    pKuroko->setFaceAngVelo(AXIS_Y, 30);
}

void VarietyRatislavia002::processBehavior() {
    EnemyRatislavia::processBehavior();
}


VarietyRatislavia002::~VarietyRatislavia002() {
}
