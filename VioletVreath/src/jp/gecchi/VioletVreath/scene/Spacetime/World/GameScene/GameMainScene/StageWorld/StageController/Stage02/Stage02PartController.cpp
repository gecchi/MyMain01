#include "Stage02PartController.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02.h"
#include "part/Stage02_01.h"
#include "part/Stage02_Climax.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_FAINAL ,
    PROG_BANPEI,
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
    useProgress(PROG_BANPEI);
}

void Stage02PartController::initialize() {
    getProgress()->change(PROG_INIT);
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

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->hasJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("Stage02PartController::PROG_FAINALきた");
            }
            if (pProg->hasArrivedAt(60)) {
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
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STAGE02_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE02_01_WAS_FINISHED");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE02_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE02_CLIMAX_WAS_FINISHEDキャッチした。STAGE02PARTCONTROLLER_ENDINGを投げる");
        ((Stage*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //進捗をStage02PartController::PROG_FAINALに切り替える
    } else {

    }
}

Stage02PartController::~Stage02PartController() {

}
