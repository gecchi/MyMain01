#include "stdafx.h"
#include "actor/Teki002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperC.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

Teki002::Teki002(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "jiki") { //Guruguru.x が参照される。
    pAxMvr_ = NEW GgafDxAxesMover(this);
}

void Teki002::initialize() {
    setScaleR(10.0);

//    _pKuroko->setMvAngTwd(PX_C(320),0,0);
//    _pKuroko->setMvVelo(PX_C(0));
//    _pKuroko->relateFaceWithMvAng(true);
    setHitAble(true);

}

void Teki002::processBehavior() {
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_C)) {
        position(-1000000,0,0);
        pAxMvr_->setVxMvVelo(-23643);
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_SPACE)) {
        position(0,0,0);
        pAxMvr_->hlprA()->slideVxMvByVd(
                1168,1721,
                0.3, 0.4, 0, true);
    }
//    int sx = 0;
//    int sy = 0;
//    int sz = 0;
//    bool press1 = false;
//    bool pressD = false;
//    bool pressT = false;
//
//
//    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_T)) {
//        sy = 1; pressD = true;
//    }
//    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_G)) {
//        sy = 0; pressD = true;
//    }
//    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_B)) {
//        sy = -1;  pressD = true;
//    }
//    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_Y)) {
//        sy = 1; pressT = true;
//    }
//    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_H)) {
//        sy = 0; pressT = true;
//    }
//    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_N)) {
//        sy = -1;  pressT = true;
//    }
//
//
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD7)) {
//        sx = -1;  sz = 1; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD8)) {
//        sx = 0;  sz = 1; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD9)) {
//        sx = 1;  sz = 1; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD4)) {
//        sx = -1;  sz = 0; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD5)) {
//        sx = 0;  sz = 0; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD6)) {
//        sx = 1;  sz = 0; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD1)) {
//        sx = -1;  sz = -1; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD2)) {
//        sx = 0;  sz = -1; press1 = true;
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_NUMPAD3)) {
//        sx = 1;  sz = -1; press1 = true;
//    }
//
//    int tx = PX_C(100)*sx;
//    int ty = PX_C(100)*sy;
//    int tz = PX_C(100)*sz;
//
//
//    if (pressD && press1) {
//        pAxMvr_->hlprA()->slideVxyzMvByVdTo(PX_C(20),
//                tx,ty,tz,
//                0.3, 0.7, 0, true);
//    }
//    if (pressT && press1) {
//        pAxMvr_->hlprA()->slideVxyzMvByDtTo(tx,ty,tz,
//                                            60,
//                                            0.3, 0.7, 0, true);
//
//    }

//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_SPACE)) {
//        _pKuroko->setMvVelo(PX_C(2));
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
//        angle trz = UTIL::simplifyAng(_pKuroko->_angFace[AXIS_Z] + D_ANG(170));
//        _pKuroko->hlprC()->turnRzRyMvAngByDtTo(
//                trz, 0, TURN_COUNTERCLOCKWISE, false,
//                60,
//                0.5, 0.5, 0,
//                true);
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
//        angle trz = UTIL::simplifyAng(_pKuroko->_angFace[AXIS_Z] + D_ANG(170));
//        _pKuroko->hlprC()->turnRzRyMvAngByDtTo(
//                trz, 0, TURN_CLOCKWISE, false,
//                60,
//                0.5, 0.5, 0,
//                true);
//    }
//    _pKuroko->behave(); //黒衣を活動させる（Z軸回転する）

    pAxMvr_->behave();
}

Teki002::~Teki002() {
    GGAF_DELETE(pAxMvr_);
}
