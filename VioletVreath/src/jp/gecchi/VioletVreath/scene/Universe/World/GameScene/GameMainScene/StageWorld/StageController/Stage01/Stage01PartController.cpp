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
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,9100,10000,19100,20000,29100,30000};
	_paFrame_NextEvent = new frame[20];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 20;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderSceneToFactory(10000002, Stage01WalledScene, "Stage01WalledScene-2");
	orderActorToFactory(10000005, FormationAdelheid001, "FormationAdelheid001-3");
	orderActorToFactory(10000006, FormationAdelheid001, "FormationAdelheid001-4");
	orderActorToFactory(10000007, FormationAdelheid001, "FormationAdelheid001-5");
	orderActorToFactory(10000008, FormationAdelheid001, "FormationAdelheid001-6");
	orderActorToFactory(10000009, FormationAdelheid001, "FormationAdelheid001-7");
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
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				_pBgmPerformer->play_fadein(0);
				orderActorToFactory(10000010, FormationAdelheid001, "FormationAdelheid001-8");
				break;
			}
			case 200: {
				orderActorToFactory(10000011, FormationAdelheid001, "FormationAdelheid001-9");
				break;
			}
			case 300: {
				orderActorToFactory(10000012, FormationAdelheid001, "FormationAdelheid001-10");
				break;
			}
			case 400: {
				orderActorToFactory(10000013, FormationAdelheid001, "FormationAdelheid001-11");
				break;
			}
			case 500: {
				Stage01WalledScene* pWScene = (Stage01WalledScene*)obtainSceneFromFactory(10000002);
				addSubLast(pWScene);
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 600: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 700: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 800: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 900: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 1000: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 1100: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 1200: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 1300: {
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-12");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(0);
				_pBgmPerformer->play_fadein(1);
				break;
			}
			case 19100: {
				orderSceneToFactory(10000003, Stage01_03, "Stage01_03-13");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(1);
				_pBgmPerformer->play_fadein(2);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000004, Stage01_Climax, "Stage01_Climax-14");
				break;
			}
			case 30000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000004);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(2);
				_pBgmPerformer->play_fadein(3);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 20-1 ? _cnt_event+1 : _cnt_event);
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
