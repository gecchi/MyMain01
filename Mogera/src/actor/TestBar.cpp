#include "stdafx.h"
#include "TestBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperB.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

TestBar::TestBar(const char* prm_name)
      : GraphBarActor(prm_name, "TestBar") {
    _class_name = "TestBar";
    setAlpha(0.8);
}

void TestBar::initialize() {
    setScaleR(2.0);
    //_pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
    _pUvFlipper->setActivePtn(1);
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}
void TestBar::processBehavior() {
   if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
        _pKuroko->helperB()->_smthFaceAng[AXIS_Z]._prm._flg = false;
        _pKuroko->setFaceAngVelo(AXIS_Z, _pKuroko->_angveloFace[AXIS_Z] + D_ANG(2));
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
        _pKuroko->helperB()->_smthFaceAng[AXIS_Z]._prm._flg = false;
        _pKuroko->setFaceAngVelo(AXIS_Z, _pKuroko->_angveloFace[AXIS_Z] - D_ANG(2));
    }


    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
        _pKuroko->helperB()->turnCalmRzFaceAngByVdTo(
                        D_ANG(3), D_ANG(180), TURN_CLOSE_TO,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
        _pKuroko->helperB()->turnCalmRzFaceAngByVdTo(
                        D_ANG(3), D_ANG(0), TURN_CLOSE_TO,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)!!!!!");
        _pKuroko->helperB()->turnCalmRzFaceAngByDtTo(
                        D_ANG(180), TURN_CLOSE_TO, 30,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)!!!!!");
        _pKuroko->helperB()->turnCalmRzFaceAngByDtTo(
                        D_ANG(0), TURN_CLOSE_TO, 30,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_V)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_V)!!!!!");
        _pKuroko->helperB()->turnCalmRzRyFaceAngByDtTo(
                        UTIL::simplifyAng(_pKuroko->_angFace[AXIS_Z] - 10),UTIL::simplifyAng(_pKuroko->_angFace[AXIS_Y] - 10), TURN_CLOSE_TO, false, 60*5,
                        0.4, 0.6, D_ANG(0),
                        true
                    );
    }

        _TRACE_(getBehaveingFrame() << "testbar before angFace[AXIS_Z]="<<_pKuroko->_angFace[AXIS_Z] << " angveloFace[AXIS_Z]="<<_pKuroko->_angveloFace[AXIS_Z]<<" _angacceFace[AXIS_Z]="<<_pKuroko->_angacceFace[AXIS_Z]<<"");

    _pKuroko->behave();

    _TRACE_(getBehaveingFrame() << "testbar after angFace[AXIS_Z]="<<_pKuroko->_angFace[AXIS_Z] << " angveloFace[AXIS_Z]="<<_pKuroko->_angveloFace[AXIS_Z]<<" _angacceFace[AXIS_Z]="<<_pKuroko->_angacceFace[AXIS_Z]<<"");
//    _pUvFlipper->behave();
}
TestBar::~TestBar() {
}

