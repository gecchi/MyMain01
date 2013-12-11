#include "stdafx.h"
#include "actor/Teki002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperC.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

Teki002::Teki002(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "jiki") { //Guruguru.x が参照される。

}

void Teki002::initialize() {
    setScaleR(2.0);
    position(PX_C(-320),0,0);
    _pKuroko->setMvAngTwd(PX_C(320),0,0);
    _pKuroko->setMvVelo(PX_C(0));
    _pKuroko->relateFaceWithMvAng(true);
    setHitAble(true);
}

void Teki002::processBehavior() {
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_SPACE)) {
        _pKuroko->setMvVelo(PX_C(2));
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        angle trz = UTIL::simplifyAng(_pKuroko->_angFace[AXIS_Z] + D_ANG(170));
        _pKuroko->helperC()->turnCalmRzRyMvAngByDtTwd(
                trz, 0, TURN_COUNTERCLOCKWISE, false,
                60,
                0.5, 0.5, 0,
                true);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        angle trz = UTIL::simplifyAng(_pKuroko->_angFace[AXIS_Z] + D_ANG(170));
        _pKuroko->helperC()->turnCalmRzRyMvAngByDtTwd(
                trz, 0, TURN_CLOCKWISE, false,
                60,
                0.5, 0.5, 0,
                true);
    }
    _pKuroko->behave(); //黒衣を活動させる（Z軸回転する）
}

Teki002::~Teki002() {
}
