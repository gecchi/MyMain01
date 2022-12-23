#include "Stage02PartController.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02.h"
#include "part/Stage02_01.h"
#include "part/Stage02_Climax.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_FAINAL ,
    PHASE_BANPEI,
};

Stage02PartController::Stage02PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage02PartController";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,3,2100,3000};
    _paFrame_NextEvent = new frame[4];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 4;
    requestScene(70000000, Stage02_01, "Stage02_01-70000000");
    // gen01 end
}

void Stage02PartController::initialize() {
    getPhase()->change(PHASE_INIT);
}

void Stage02PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 3: {
                Stage02_01* pScene = (Stage02_01*)receiveScene(70000000);
                appendChild(pScene);
                break;
            }
            case 2100: {
                requestScene(70000001, Stage02_Climax, "Stage02_Climax-70000001");
                break;
            }
            case 3000: {
                Stage02_Climax* pScene = (Stage02_Climax*)receiveScene(70000001);
                appendChild(pScene);
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_FAINAL: {
            if (pPhase->hasJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("Stage02PartController::PHASE_FAINALきた");
            }
            if (pPhase->hasArrivedFrameAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STAGE02_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            break;
        }
        default :
            break;
    }

}


void Stage02PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    ScenePhase* pPhase = getPhase();
    if (prm_no == EVENT_STAGE02_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE02_01_WAS_FINISHED");
        ((Stage*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_no == EVENT_STAGE02_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE02_CLIMAX_WAS_FINISHEDキャッチした。STAGE02PARTCONTROLLER_ENDINGを投げる");
        ((Stage*)prm_pSource)->sayonara(SEC_F(60));
        pPhase->change(PHASE_FAINAL); //フェーズをStage02PartController::PHASE_FAINALに切り替える
    } else {

    }
}

Stage02PartController::~Stage02PartController() {

}
