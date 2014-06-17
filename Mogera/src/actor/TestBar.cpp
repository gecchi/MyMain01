#include "stdafx.h"
#include "TestBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"

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
    setMaterialColor(0.3, 1.0, 0.3);
    //_pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
    _pUvFlipper->setActivePtn(1);
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}
void TestBar::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
   if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
        pKuroko->asstB()->_smthFaceAng[AXIS_Z]._prm._flg = false;
        pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angveloFace[AXIS_Z] + D_ANG(2));
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
        pKuroko->asstB()->_smthFaceAng[AXIS_Z]._prm._flg = false;
        pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angveloFace[AXIS_Z] - D_ANG(2));
    }


    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
        pKuroko->asstB()->turnRzFaceAngByVdTo(
                        D_ANG(3), D_ANG(180), TURN_CLOSE_TO,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
        pKuroko->asstB()->turnRzFaceAngByVdTo(
                        D_ANG(3), D_ANG(0), TURN_CLOSE_TO,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)!!!!!");
        pKuroko->asstB()->turnRzFaceAngByDtTo(
                        D_ANG(180), TURN_ANTICLOSE_TO, 30,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)!!!!!");
        pKuroko->asstB()->turnRzFaceAngByDtTo(
                        D_ANG(0), TURN_ANTICLOSE_TO, 30,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_C)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_C)!!!!!");
        pKuroko->asstB()->turnFaceAngByDt(AXIS_Z,
                        D_ANG(360+360), 60,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_V)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_V)!!!!!");
        pKuroko->asstB()->turnFaceAngByDt(AXIS_Z,
                        D_ANG(-360-360), 60,
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_B)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_B)!!!!!");
        pKuroko->asstB()->turnFaceAngByVd(AXIS_Z,
                        D_ANG(10),  D_ANG(360+360),
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_N)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_N)!!!!!");
        pKuroko->asstB()->turnFaceAngByVd(AXIS_Z,
                        D_ANG(10), D_ANG(-360-360),
                        0.3, 0.6, D_ANG(0),
                        true
                    );
    }

    _TRACE_(getBehaveingFrame() << "testbar before _apActorFaceAng[AXIS_Z]="<<(*(pKuroko->_apActorFaceAng[AXIS_Z])) << " angveloFace[AXIS_Z]="<<pKuroko->_angveloFace[AXIS_Z]<<" _angacceFace[AXIS_Z]="<<pKuroko->_angacceFace[AXIS_Z]<<"");

    pKuroko->behave();

    _TRACE_(getBehaveingFrame() << "testbar after _apActorFaceAng[AXIS_Z]="<<(*(pKuroko->_apActorFaceAng[AXIS_Z])) << " angveloFace[AXIS_Z]="<<pKuroko->_angveloFace[AXIS_Z]<<" _angacceFace[AXIS_Z]="<<pKuroko->_angacceFace[AXIS_Z]<<"");
//    _pUvFlipper->behave();
}
TestBar::~TestBar() {
}

