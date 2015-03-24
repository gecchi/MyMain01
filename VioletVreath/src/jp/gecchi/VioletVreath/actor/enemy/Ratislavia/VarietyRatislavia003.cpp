#include "VarietyRatislavia003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Omulus/EnemyOmulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia003::VarietyRatislavia003(const char* prm_name) : EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia003";
    for (angle angPos1 = D0ANG; angPos1 < D360ANG;  angPos1 += D_ANG(60)) {
        for (angle angPos2 = D0ANG; angPos2 < D360ANG;  angPos2 += D_ANG(20)) {
            EnemyOmulus* p = NEW EnemyOmulus("pEV1");
            addSubGroupAsFkOnSurface(p, angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietyRatislavia003::initialize() {
    EnemyRatislavia::initialize();
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    _x = pSpacetime->_x_gone_right + r1_ + r2_;
    _y = 0;
    _z = MyShip::lim_z_right_;
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRzRyMvAng(D180ANG, 0);
    pKuroko->setMvVelo(3000);
    pKuroko->setFaceAngVelo(AXIS_Z, -20);
    pKuroko->setFaceAngVelo(AXIS_Y, 10);
}

void VarietyRatislavia003::processBehavior() {
    EnemyRatislavia::processBehavior();
}


VarietyRatislavia003::~VarietyRatislavia003() {
}
