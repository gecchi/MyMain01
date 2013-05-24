#include "stdafx.h"
#include "VarietySylvia003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Romulus/EnemyRomulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/EnemySylviaEye.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietySylvia003::VarietySylvia003(const char* prm_name) : EnemySylvia(prm_name, "Sylvia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietySylvia003";
    for (angle angPos1 = D0ANG; angPos1 < D360ANG;  angPos1 += D_ANG(60)) {
        for (angle angPos2 = D0ANG; angPos2 < D360ANG;  angPos2 += D_ANG(20)) {
            EnemyRomulus* p = NEW EnemyRomulus("pEV1");
            addSubGroupAsFkOnSurface(p, angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietySylvia003::initialize() {
    EnemySylvia::initialize();
    _X = GgafDxCore::GgafDxUniverse::_X_gone_right+r1_+r2_;
    _Y = 0;
    _Z = MyShip::lim_zright_;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -20);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 10);
}

void VarietySylvia003::processBehavior() {
    EnemySylvia::processBehavior();
}


VarietySylvia003::~VarietySylvia003() {
}
