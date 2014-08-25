#include "DefaultD3DXAniMeshTestActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


DefaultD3DXAniMeshTestActor::DefaultD3DXAniMeshTestActor(const char* prm_name) :
        DefaultD3DXAniMeshActor(prm_name, "_chk_DefaultD3DXAniMeshTestModel", nullptr) {
    _class_name = "DefaultD3DXAniMeshTestActor";
    setHitAble(false);
}

void DefaultD3DXAniMeshTestActor::processBehavior() {
//    if (GgafDxInput::isPushedDownKey(DIK_0)) {
//        _pPuppeteer->play(LEFT_HAND,
//                            0,          //UINT   prm_performance_no,
//                            -1,         //double prm_loopnum,
//                            3.0,        //double prm_target_speed,
//                            0,          //frame  prm_shift_speed_frames,
//                            1.0,        //double prm_target_weight,
//                            0    );     //frame  prm_shift_weight_frames
//
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_9)) {
//        _pPuppeteer->play(LEFT_HAND,
//                            1,          //UINT   prm_performance_no,
//                            -1,         //double prm_loopnum,
//                            -10.0,      //double prm_target_speed,
//                            120,        //frame  prm_shift_speed_frames,
//                            1.0,        //double prm_target_weight,
//                            0    );     //frame  prm_shift_weight_frames
//    }
//
//    if (GgafDxInput::isPushedDownKey(DIK_8)) {
//        _pPuppeteer->exchangPerformance();
//    }
//
//    _pPuppeteer->behave();

}

DefaultD3DXAniMeshTestActor::~DefaultD3DXAniMeshTestActor() {
}

