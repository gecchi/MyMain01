#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TamagoActor::TamagoActor(const char* prm_name, GgafStatus* prm_pStat) :
        DefaultD3DXAniMeshActor(prm_name, "anibox", NULL) {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    setScale(2000);
}

void TamagoActor::processBehavior() {
    if (GgafDxInput::isPushedDownKey(DIK_0)) {
        _pPuppeteer->play(LEFT_HAND,
                            0,          //UINT   prm_performance_no,
                            -1,         //double prm_loopnum,
                            3.0,        //double prm_target_speed,
                            0,          //frame  prm_shift_speed_frames,
                            1.0,        //double prm_target_weight,
                            0    );     //frame  prm_shift_weight_frames

    }
    if (GgafDxInput::isPushedDownKey(DIK_9)) {
        _pPuppeteer->exchangPerformance();
        _pPuppeteer->play(LEFT_HAND,
                            1,          //UINT   prm_performance_no,
                            -1,         //double prm_loopnum,
                            -10.0,      //double prm_target_speed,
                            120,        //frame  prm_shift_speed_frames,
                            1.0,        //double prm_target_weight,
                            0    );     //frame  prm_shift_weight_frames
    }
    if (GgafDxInput::isPushedDownKey(DIK_8)) {
//        _pPuppeteer->play(1, 1.0, LOOP_MOTION_LINER);
    }
    if (GgafDxInput::isPushedDownKey(DIK_7)) {
//        _pPuppeteer->play(1, -1.0, LOOP_MOTION_LINER);
    }
    if (GgafDxInput::isPushedDownKey(DIK_6)) {
//        _pPuppeteer->exchangStick();
    }

    if (GgafDxInput::isPushedDownKey(DIK_E)) {
    }

    if (GgafDxInput::isPushedDownKey(DIK_R)) {
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
