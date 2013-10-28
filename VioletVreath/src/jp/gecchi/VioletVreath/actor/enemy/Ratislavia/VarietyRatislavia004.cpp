#include "stdafx.h"
#include "VarietyRatislavia004.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Omulus/EnemyOmulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia004::VarietyRatislavia004(const char* prm_name) : EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia004";
    for (angle angPos1 = D0ANG; angPos1 < D360ANG;  angPos1 += D_ANG(20)) {
        for (angle angPos2 = D0ANG; angPos2 < D360ANG;  angPos2 += D_ANG(20)) {
            EnemyOmulus* p = NEW EnemyOmulus("pEV1");
            addSubGroupAsFkOnSurface(p, angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietyRatislavia004::initialize() {
    EnemyRatislavia::initialize();
    _x = GgafDxCore::GgafDxUniverse::_x_gone_right+r1_+r2_;
    _y = MyShip::lim_y_bottom_;
    _z = 0;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -20);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 10);
}

void VarietyRatislavia004::processBehavior() {
    EnemyRatislavia::processBehavior();
}

VarietyRatislavia004::~VarietyRatislavia004() {
}
