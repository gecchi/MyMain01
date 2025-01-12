#include "TamagoActor.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"



using namespace GgafLib;
using namespace VioletVreath;

TamagoActor::TamagoActor(const char* prm_name) :
        DefaultBoneAniMeshActor(prm_name, "anibox") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    setScale(2000);
}

void TamagoActor::processBehavior() {
//    if (GgafDx::Input::isPushedDownKey(DIK_0)) {
//        _pPuppeteer->play(LEFT_HAND,
//                            0,          //UINT   prm_performance_no,
//                            -1,         //double prm_loopnum,
//                            3.0,        //double prm_target_speed,
//                            0,          //frame  prm_shift_speed_frames,
//                            1.0,        //double prm_target_weight,
//                            0    );     //frame  prm_shift_weight_frames
//
//    }
//    if (GgafDx::Input::isPushedDownKey(DIK_9)) {
//        _pPuppeteer->exchangPerformance();
//        _pPuppeteer->play(LEFT_HAND,
//                            1,          //UINT   prm_performance_no,
//                            -1,         //double prm_loopnum,
//                            -10.0,      //double prm_target_speed,
//                            120,        //frame  prm_shift_speed_frames,
//                            1.0,        //double prm_target_weight,
//                            0    );     //frame  prm_shift_weight_frames
//    }
//    if (GgafDx::Input::isPushedDownKey(DIK_8)) {
////        _pPuppeteer->play(1, 1.0, LOOP_MOTION_LINEAR);
//    }
//    if (GgafDx::Input::isPushedDownKey(DIK_7)) {
////        _pPuppeteer->play(1, -1.0, LOOP_MOTION_LINEAR);
//    }
//    if (GgafDx::Input::isPushedDownKey(DIK_6)) {
////        _pPuppeteer->exchangStick();
//    }
//
//    if (GgafDx::Input::isPushedDownKey(DIK_E)) {
//    }
//
//    if (GgafDx::Input::isPushedDownKey(DIK_R)) {
//    }

    _pPuppeteer->behave();

}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    _TRACE_("TamagoActorƒqƒbƒg‚µ‚Ü‚µ‚½B("<<_x<<","<<_y<<","<<_z<<")");
}

TamagoActor::~TamagoActor() {
}
