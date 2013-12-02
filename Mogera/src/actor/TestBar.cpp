#include "stdafx.h"
#include "TestBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"

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
    //_pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(1));
    _pUvFlipper->setActivePtn(1);
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}
void TestBar::processBehavior() {
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
//        _pKurokoA->turnSmoothlyRzFaceAngByDtTo(
//                        D_ANG(180), TURN_CLOCKWISE,
//                        0, 60*3,
//                        0.3, 0.6,
//                        true
//                    );
//    }
//    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
//        _pKurokoA->turnSmoothlyRzFaceAngByDtTo(
//                        D_ANG(0), TURN_COUNTERCLOCKWISE,
//                        0, 60*3,
//                        0.3, 0.6,
//                        true
//                    );
//    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_D)!!!!!");
        _pKurokoA->_smooth_turn_rz_faceang_flg = false;
        _pKurokoA->setFaceAngVelo(AXIS_Z, _pKurokoA->_angveloFace[AXIS_Z] + D_ANG(2));
    }
        if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_F)!!!!!");
        _pKurokoA->_smooth_turn_rz_faceang_flg = false;
        _pKurokoA->setFaceAngVelo(AXIS_Z, _pKurokoA->_angveloFace[AXIS_Z] - D_ANG(2));
    }

    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_A)!!!!!");
        _pKurokoA->turnSmoothlyRzFaceAngByVdTo(
                        D_ANG(180), TURN_CLOSE_TO,
                        D_ANG(10), D_ANG(0),
                        0.3, 0.6,
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_S)!!!!!");
        _pKurokoA->turnSmoothlyRzFaceAngByVdTo(
                        D_ANG(0), TURN_CLOSE_TO,
                        D_ANG(10), D_ANG(0),
                        0.3, 0.6,
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Z)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_Q)!!!!!");
        _pKurokoA->turnSmoothlyRzFaceAngByDtTo(
                        D_ANG(180), TURN_CLOSE_TO,
                        D_ANG(0),120,
                        0.3, 0.6,
                        true
                    );
    }
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_X)) {
        _TRACE_("GgafDxCore::GgafDxInput::isPushedDownKey(DIK_W)!!!!!");
        _pKurokoA->turnSmoothlyRzFaceAngByDtTo(
                        D_ANG(0), TURN_CLOSE_TO,
                        D_ANG(0),120,
                        0.3, 0.6,
                        true
                    );
    }
//    void turnSmoothlyRzFaceAngByDtTo(
//            angle prm_angRz_Target,
//            int prm_way, bool prm_optimize_ang,
//            angvelo prm_end_angvelo,
//            int prm_target_frames, float prm_p1, float prm_p2,
//            bool prm_endacc_flg = true);


    _pKurokoA->behave();
//    _pUvFlipper->behave();
}
TestBar::~TestBar() {
}

