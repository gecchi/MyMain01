#include "stdafx.h"
#include "VarietyRatislavia002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
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
            addSubGroupAsFkOnSurface(NEW EnemyEmus(name.c_str()), angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietyRatislavia002::initialize() {
    EnemyRatislavia::initialize();
    _X = GgafDxCore::GgafDxUniverse::_X_gone_right+r1_+r2_;
    _Y = 0;
    _Z = MyShip::lim_Z_left_;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(1000);
    _pKurokoA->setFaceAngVelo(AXIS_X, 10);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -50);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 30);
}

void VarietyRatislavia002::processBehavior() {
    EnemyRatislavia::processBehavior();
}


VarietyRatislavia002::~VarietyRatislavia002() {
}
