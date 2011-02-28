#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "anibox") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    setScale(2000);
}

void TamagoActor::processBehavior() {
    if (GgafDx9Input::isPushedDownKey(DIK_0)) {
        _pPuppeteer->play(LEFT_HAND,
                            0,          //UINT   prm_performance_no,
                            -1,        //double prm_loopnum,
                            3.0,        //double prm_target_speed,
                            0,          //frame  prm_frame_duaration_of_shift_speed,
                            1.0,        //double prm_target_weight,
                            0    );     //frame  prm_frame_duaration_of_shift_weight

    }
    if (GgafDx9Input::isPushedDownKey(DIK_9)) {
        _pPuppeteer->exchangPerformance();
        _pPuppeteer->play(LEFT_HAND,
                            1,          //UINT   prm_performance_no,
                            -1,        //double prm_loopnum,
                            -3.0,       //double prm_target_speed,
                            0,          //frame  prm_frame_duaration_of_shift_speed,
                            1.0,        //double prm_target_weight,
                            0    );     //frame  prm_frame_duaration_of_shift_weight
    }
    if (GgafDx9Input::isPushedDownKey(DIK_8)) {
//        _pPuppeteer->play(1, 1.0, LOOP_MOTION_LINER);
    }
    if (GgafDx9Input::isPushedDownKey(DIK_7)) {
//        _pPuppeteer->play(1, -1.0, LOOP_MOTION_LINER);
    }
    if (GgafDx9Input::isPushedDownKey(DIK_6)) {
//        _pPuppeteer->exchangStick();
    }

    if (GgafDx9Input::isPushedDownKey(DIK_E)) {
    }

    if (GgafDx9Input::isPushedDownKey(DIK_R)) {
    }

    _pPuppeteer->behave();

}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("TamagoActorƒqƒbƒg‚µ‚Ü‚µ‚½B("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
