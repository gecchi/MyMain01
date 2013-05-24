#include "stdafx.h"
#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(4);
    _pBgmPerformer->set(0, "OGG_BGM_01_01");
    _pBgmPerformer->set(1, "OGG_BGM_01_02");
    _pBgmPerformer->set(2, "OGG_BGM_01_03");
    _pBgmPerformer->set(3, "OGG_BGM_01_CLIMAX");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300};
    _paFrame_NextEvent = new frame[14];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 14;
    orderActorToFactory(10000000, FormationAdelheid001, "FormationAdelheid001-1");
    orderActorToFactory(10000001, FormationAdelheid001, "FormationAdelheid001-2");
    orderActorToFactory(10000002, FormationAdelheid001, "FormationAdelheid001-3");
    orderActorToFactory(10000003, FormationAdelheid001, "FormationAdelheid001-4");
    orderActorToFactory(10000004, FormationAdelheid001, "FormationAdelheid001-5");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->reset(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getActiveFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getActiveFrame()) {
            case 1: {
                break;
            }
            case 100: {
                orderActorToFactory(10000005, FormationAdelheid001, "FormationAdelheid001-6");
                break;
            }
            case 200: {
                orderActorToFactory(10000006, FormationAdelheid001, "FormationAdelheid001-7");
                break;
            }
            case 300: {
                orderActorToFactory(10000007, FormationAdelheid001, "FormationAdelheid001-8");
                break;
            }
            case 400: {
                orderActorToFactory(10000008, FormationAdelheid001, "FormationAdelheid001-9");
                break;
            }
            case 500: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000000);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
                break;
            }
            case 600: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000001);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
                break;
            }
            case 700: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000002);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
                break;
            }
            case 800: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000003);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
                break;
            }
            case 900: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000004);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
                break;
            }
            case 1000: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000005);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
                break;
            }
            case 1100: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000006);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
                break;
            }
            case 1200: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000007);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
                break;
            }
            case 1300: {
                FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000008);
                getSceneDirector()->addSubGroup(pF);
                pF->locate(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 14-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (_pProg->getFrameInProgress() == 60) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((Stage*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
